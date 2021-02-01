#include <Arduino.h>
#include "wifiSniffer.h"
#include "fileDatabase.h"
#include "ntp.h"
#include "config.h"
#include "test.h"
#include "random.h"
#include <ArduinoJson.h>
#include <FS.h>

extern "C"
{
#include <user_interface.h>
}

static os_timer_t channelHop_timer;

/**
 * Callback for promiscuous mode
 */
static void ICACHE_FLASH_ATTR wifisniffer_callback(uint8_t *buffer, uint16_t length)
{
    struct SnifferPacket *snifferPacket = (struct SnifferPacket *)buffer;
    processMetadata(snifferPacket);
}

static void printDataSpan(uint16_t start, uint16_t size, uint8_t *data)
{
    for (uint16_t i = start; i < DATA_LENGTH && i < start + size; i++)
    {
        Serial.write(data[i]);
    }
}

static String getDataSpan(uint16_t start, uint16_t size, uint8_t *data)
{
    String content = "";

    for (uint16_t i = start; i < DATA_LENGTH && i < start + size; i++)
    {
        char character = data[i];
        content += String(character);
    }

    //Serial.printf("The %d-length SSID is: ", size);
    //Serial.println(content);

    return content;
}

static void getMAC(char *macAddress, uint8_t *data, uint16_t offset)
{
    sprintf(macAddress, "%02x:%02x:%02x:%02x:%02x:%02x", data[offset + 0], data[offset + 1], data[offset + 2], data[offset + 3], data[offset + 4], data[offset + 5]);
}

/**
 * Callback for channel hoping
 */
void channelHop()
{
    // hoping channels 1-13
    uint8 new_channel = wifi_get_channel() + 1;
    if (new_channel > 13)
    {
        new_channel = 1;
    }
    wifi_set_channel(new_channel);

    //Serial.printf("Hopped to channel %d\n", new_channel);
}

static void writeMetadataAsCSV(SnifferPacket *snifferPacket, signed int rssi, uint8 wifiChannel, const char *macAddress, uint8_t SSID_length)
{
    // RSSI
    char buffer[7];
    itoa(rssi, buffer, 10); //(integer, yourBuffer, base)
    fdb_write(WIFIDEVICES_FILE_CSV, buffer);
    fdb_write(WIFIDEVICES_FILE_CSV, ",");

    // channel
    itoa(wifiChannel, buffer, 10);
    fdb_write(WIFIDEVICES_FILE_CSV, buffer);
    fdb_write(WIFIDEVICES_FILE_CSV, ",");

    // MAC address
    fdb_write(WIFIDEVICES_FILE_CSV, macAddress);
    fdb_write(WIFIDEVICES_FILE_CSV, ",");

    // SSID length
    itoa(SSID_length, buffer, 10); //(integer, yourBuffer, base)
    fdb_write(WIFIDEVICES_FILE_CSV, buffer);
    fdb_write(WIFIDEVICES_FILE_CSV, ",");

    // ISO-8601 datetime
    fdb_write(WIFIDEVICES_FILE_CSV, getFormattedDateTime().c_str());
    fdb_write(WIFIDEVICES_FILE_CSV, ",");

    // SSID
    fdb_write(WIFIDEVICES_FILE_CSV, getDataSpan(26, SSID_length, snifferPacket->data).c_str());
    fdb_write(WIFIDEVICES_FILE_CSV, ",");

    // UUID
    uint8_t uuid_array[16];
    ESPRandom::uuid(uuid_array);
    fdb_write(WIFIDEVICES_FILE_CSV, ESPRandom::uuidToString(uuid_array).c_str());

    fdb_write(WIFIDEVICES_FILE_CSV, "\n");
}

static void writeMetadataAsJSON(SnifferPacket *snifferPacket, signed int rssi, uint8 wifiChannel, const char *macAddress, uint8_t SSID_length)
{
    Serial.println("Writing WiFi-Log to JSON...");

    // UUID
    uint8_t uuid_array[16];
    ESPRandom::uuid(uuid_array);

    const size_t capacity = JSON_OBJECT_SIZE(7) + 160;
    DynamicJsonDocument jsonDocument(capacity);

    jsonDocument["RSSI"] = rssi;
    jsonDocument["Channel"] = wifiChannel;
    jsonDocument["MAC"] = macAddress;
    jsonDocument["DateTime"] = getFormattedDateTime();
    jsonDocument["UUID"] = ESPRandom::uuidToString(uuid_array);
    jsonDocument["SSID"] = getDataSpan(26, SSID_length, snifferPacket->data);

    File file = fdb_openStream(WIFIDEVICES_FILE_JSON, "a");
    serializeJson(jsonDocument, file);
    file.close();
}

static void writeMetadataAsMsgPack(SnifferPacket *snifferPacket, signed int rssi, uint8 wifiChannel, const char *macAddress, uint8_t SSID_length)
{
    Serial.println("Writing WiFi-Log to JSON...");

    // UUID
    uint8_t uuid_array[16];
    ESPRandom::uuid(uuid_array);

    const size_t capacity = JSON_OBJECT_SIZE(7) + 160;
    DynamicJsonDocument jsonDocument(capacity);

    jsonDocument["RSSI"] = rssi;
    jsonDocument["Channel"] = wifiChannel;
    jsonDocument["MAC"] = macAddress;
    jsonDocument["DateTime"] = getFormattedDateTime();
    jsonDocument["UUID"] = ESPRandom::uuidToString(uuid_array);
    jsonDocument["SSID"] = getDataSpan(26, SSID_length, snifferPacket->data);

    File file = fdb_openStream(WIFIDEVICES_FILE_MSGPACK, "a");
    serializeMsgPack(jsonDocument, file);
    file.close();
}

static void printMetadata(SnifferPacket *snifferPacket, signed int rssi, uint8 wifiChannel, const char *macAddress, uint8_t SSID_length)
{
    Serial.print("RSSI=");
    Serial.print(rssi);

    Serial.print(" Channel=");
    Serial.print(wifiChannel);

    Serial.print(" MAC=");
    Serial.print(macAddress);

    Serial.print(" SSID='");
    printDataSpan(26, SSID_length, snifferPacket->data);
    Serial.print("'");

    Serial.println();
}

static void processMetadata(SnifferPacket *snifferPacket)
{
    unsigned int frameControl = ((unsigned int)snifferPacket->data[1] << 8) + snifferPacket->data[0];

    uint8_t version = (frameControl & 0b0000000000000011) >> 0;
    uint8_t frameType = (frameControl & 0b0000000000001100) >> 2;
    uint8_t frameSubType = (frameControl & 0b0000000011110000) >> 4;
    uint8_t toDS = (frameControl & 0b0000000100000000) >> 8;
    uint8_t fromDS = (frameControl & 0b0000001000000000) >> 9;

    // Only look for probe request packets
    if (frameType != TYPE_MANAGEMENT ||
        frameSubType != SUBTYPE_PROBE_REQUEST)
    {
        return;
    }

    signed int rssi = snifferPacket->rx_ctrl.rssi;

    uint8 wifiChannel = wifi_get_channel();

    char macAddress[] = "00:00:00:00:00:00";
    getMAC(macAddress, snifferPacket->data, 10);

    uint8_t SSID_length = snifferPacket->data[25];

    printMetadata(snifferPacket, rssi, wifiChannel, macAddress, SSID_length);
    //writeMetadataAsCSV(snifferPacket, rssi, wifiChannel, macAddress, SSID_length);
    //writeMetadataAsJSON(snifferPacket, rssi, wifiChannel, macAddress, SSID_length);
    writeMetadataAsMsgPack(snifferPacket, rssi, wifiChannel, macAddress, SSID_length);
}

void wifisniffer_setup()
{
    // set the WiFi chip to promiscuous mode
    delay(10);
    wifi_set_opmode(STATION_MODE);
    wifi_set_channel(1);
    wifi_promiscuous_enable(DISABLE);
    delay(10);
    wifi_set_promiscuous_rx_cb(wifisniffer_callback);
    delay(10);
    wifi_promiscuous_enable(ENABLE);

    // setup the channel hoping callback timer
    os_timer_disarm(&channelHop_timer);
    os_timer_setfn(&channelHop_timer, (os_timer_func_t *)channelHop, NULL);
    os_timer_arm(&channelHop_timer, CHANNEL_HOP_INTERVAL_MS, 1);
}