#ifndef HELLOWORLDARDUINO_SENSORS_H
#define HELLOWORLDARDUINO_SENSORS_H

#include <Arduino.h>

void publish_sensor_data();

u_int8_t get_wifi_networks_count();

int8_t get_wifi_rssi();

boolean get_wifi_autoreconnect();

boolean get_wifi_autoconnect();

String get_wifi_local_ip();

String get_wifi_mac_address();

String get_wifi_station_bssid();

String get_wifi_hostname();

int8_t get_wifi_listen_interval();

void publish_wifi_data();

void publish_time_data();

void publish_device_information();

#endif //HELLOWORLDARDUINO_SENSORS_H
