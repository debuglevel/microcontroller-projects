#include <ESP8266WiFi.h>
#include "sensors.h"
#include "mqtt.h"
#include "ntp.h"

void publish_sensor_data() {
    publish_wifi_data();

    mqtt_send_message("datetime", getFormattedDateTime().c_str());
}

void publish_wifi_data() {
    // about the environment
    mqtt_send_message("wifi-networks-count", String(get_wifi_networks_count()).c_str());

    // about the device configuration
    mqtt_send_message("wifi-device-listen-interval", String(get_wifi_listen_interval()).c_str());
    mqtt_send_message("wifi-device-autoconnect", String(get_wifi_autoconnect()).c_str());
    mqtt_send_message("wifi-device-autoreconnect", String(get_wifi_autoreconnect()).c_str());

    // invariable facts about the device
    mqtt_send_message("wifi-device-mac-address", get_wifi_mac_address().c_str());

    // invariable facts about the station
    mqtt_send_message("wifi-station-bssid", get_wifi_station_bssid().c_str());

    // about the connection
    mqtt_send_message("wifi-device-hostname", get_wifi_hostname().c_str());
    mqtt_send_message("wifi-device-ip", get_wifi_local_ip().c_str());
    mqtt_send_message("wifi-connection-rssi", String(get_wifi_rssi()).c_str());
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