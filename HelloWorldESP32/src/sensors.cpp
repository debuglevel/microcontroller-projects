#include <WiFi.h>
#include "sensors.h"
#include "mqtt.h"
#include "ntp.h"

void publish_sensor_data() {
    publish_wifi_data();
    publish_time_data();
    publish_device_information();
}

// Mimics the behavior on a ESP8266 based on the MAC address
uint32_t getChipId()
{
    uint32_t chipId = 0;

	for(int i=0; i<17; i=i+8) {
	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;  
	}

    return chipId;
}

void publish_device_information() {
    mqtt_send_message("device/chip/id", String(getChipId()));
    mqtt_send_message("device/chip/model", String(ESP.getChipModel()));
    mqtt_send_message("device/chip/revision", String(ESP.getChipRevision()));
    mqtt_send_message("device/chip/cores", String(ESP.getChipCores()));
    //mqtt_send_message("device/boot/version", String(ESP.getBootVersion())); // Not available for ESP32
    //mqtt_send_message("device/boot/mode", String(ESP.getBootMode())); // Not available for ESP32
    //mqtt_send_message("device/boot/reset/info", String(ESP.getResetInfo())); // Not available for ESP32
    //mqtt_send_message("device/boot/reset/reason", String(ESP.getResetReason())); // Not available for ESP32
    mqtt_send_message("device/sdk/version/short", String(ESP.getSdkVersion()));
    //mqtt_send_message("device/sdk/version/full", String(ESP.getFullVersion())); // Not available for ESP32
    //mqtt_send_message("device/core/version", String(ESP.getCoreVersion())); // Not available for ESP32
    mqtt_send_message("device/cpu/frequency/mhz", String(ESP.getCpuFreqMHz()));
    mqtt_send_message("device/flash/size", String(ESP.getFlashChipSize()));
    //mqtt_send_message("device/flash/real-size", String(ESP.getFlashChipRealSize())); // Not available for ESP32
    mqtt_send_message("device/flash/speed", String(ESP.getFlashChipSpeed()));
    //mqtt_send_message("device/flash/id", String(ESP.getFlashChipId())); // Not available for ESP32
    mqtt_send_message("device/flash/mode", String(ESP.getFlashChipMode()));
    //mqtt_send_message("device/flash/vendor/id", String(ESP.getFlashChipVendorId())); // Not available for ESP32
    mqtt_send_message("device/memory/heap/free", String(ESP.getFreeHeap()));
    //mqtt_send_message("device/memory/heap/fragmentation", String(ESP.getHeapFragmentation())); // Not available for ESP32
    
    // TODO: There are some others for ESP32
}

void publish_time_data() {
    mqtt_send_message("datetime", getFormattedDateTime().c_str());

    int64_t uptimeSeconds = millis() / 1000;
    mqtt_send_message("uptime/seconds", String(uptimeSeconds));
    mqtt_send_message("uptime/minutes", String((double) uptimeSeconds / 60));
    mqtt_send_message("uptime/hours", String((double) uptimeSeconds / 60 / 60));
    mqtt_send_message("uptime/days", String((double) uptimeSeconds / 60 / 60 / 24));
}

void publish_wifi_data() {
    // about the environment
    mqtt_send_message("wifi/networks-count", String(get_wifi_networks_count()));

    // about the device configuration
    //mqtt_send_message("wifi/device/listen-interval", String(get_wifi_listen_interval())); // Not available for ESP32
    mqtt_send_message("wifi/device/autoconnect", String(get_wifi_autoconnect()));
    mqtt_send_message("wifi/device/autoreconnect", String(get_wifi_autoreconnect()));

    // invariable facts about the device
    mqtt_send_message("wifi/device/mac-address", get_wifi_mac_address());

    // invariable facts about the station
    mqtt_send_message("wifi/station/bssid", get_wifi_station_bssid());

    // about the connection
    //mqtt_send_message("wifi/device/hostname", get_wifi_hostname()); // Not available for ESP32
    mqtt_send_message("wifi/device/ip", get_wifi_local_ip());
    mqtt_send_message("wifi/connection/rssi", String(get_wifi_rssi()));
}

u_int8_t get_wifi_networks_count() {
    // CAVEAT: needs quite a long time and probably disconnects from the station while scanning
    return WiFi.scanNetworks(false, true, 0, NULL);
}

int8_t get_wifi_rssi() {
    return WiFi.RSSI();
}

String get_wifi_local_ip() {
    return WiFi.localIP().toString();
}

String get_wifi_mac_address() {
    return WiFi.macAddress();
}

String get_wifi_station_bssid() {
    return WiFi.BSSIDstr();
}

// String get_wifi_hostname() {
//     return WiFi.hostname();
// }

// int8_t get_wifi_listen_interval() {
//     return WiFi.getListenInterval();
// }

boolean get_wifi_autoconnect() {
    return WiFi.getAutoConnect();
}

boolean get_wifi_autoreconnect() {
    return WiFi.getAutoReconnect();
}