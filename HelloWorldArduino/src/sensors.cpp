#include <ESP8266WiFi.h>
#include "sensors.h"
#include "mqtt.h"
#include "ntp.h"

void publish_sensor_data() {
    publish_wifi_data();
    publish_time_data();
    publish_device_information();
}

void publish_device_information() {
    mqtt_send_message("chip-id", String(ESP.getChipId()));
    mqtt_send_message("boot-version", String(ESP.getBootVersion()));
    mqtt_send_message("sdk-version", String(ESP.getSdkVersion()));
    mqtt_send_message("core-version", String(ESP.getCoreVersion()));
    mqtt_send_message("cpu-frequency", String(ESP.getCpuFreqMHz()));
    mqtt_send_message("flash-size", String(ESP.getFlashChipSize()));
    mqtt_send_message("flash-real-size", String(ESP.getFlashChipRealSize()));
    mqtt_send_message("flash-speed", String(ESP.getFlashChipSpeed()));
    mqtt_send_message("free-heap", String(ESP.getFreeHeap()));
    mqtt_send_message("full-version", String(ESP.getFullVersion()));
}

void publish_time_data() {
    mqtt_send_message("datetime", getFormattedDateTime().c_str());

    int64_t uptimeSeconds = millis() / 1000;
    mqtt_send_message("uptime-seconds", String(uptimeSeconds));
    mqtt_send_message("uptime-minutes", String((double) uptimeSeconds / 60));
    mqtt_send_message("uptime-hours", String((double) uptimeSeconds / 60 / 60));
    mqtt_send_message("uptime-days", String((double) uptimeSeconds / 60 / 60 / 24));
}

void publish_wifi_data() {
    // about the environment
    mqtt_send_message("wifi-networks-count", String(get_wifi_networks_count()));

    // about the device configuration
    mqtt_send_message("wifi-device-listen-interval", String(get_wifi_listen_interval()));
    mqtt_send_message("wifi-device-autoconnect", String(get_wifi_autoconnect()));
    mqtt_send_message("wifi-device-autoreconnect", String(get_wifi_autoreconnect()));

    // invariable facts about the device
    mqtt_send_message("wifi-device-mac-address", get_wifi_mac_address());

    // invariable facts about the station
    mqtt_send_message("wifi-station-bssid", get_wifi_station_bssid());

    // about the connection
    mqtt_send_message("wifi-device-hostname", get_wifi_hostname());
    mqtt_send_message("wifi-device-ip", get_wifi_local_ip());
    mqtt_send_message("wifi-connection-rssi", String(get_wifi_rssi()));
}

u_int8_t get_wifi_networks_count() {
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

String get_wifi_hostname() {
    return WiFi.hostname();
}

int8_t get_wifi_listen_interval() {
    return WiFi.getListenInterval();
}

boolean get_wifi_autoconnect() {
    return WiFi.getAutoConnect();
}

boolean get_wifi_autoreconnect() {
    return WiFi.getAutoReconnect();
}