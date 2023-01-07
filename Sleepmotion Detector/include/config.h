#ifndef HELLOWORLDARDUINO_CONFIG_H
#define HELLOWORLDARDUINO_CONFIG_H

#define WIFI_SSID "Pretty Fly For a WiFi 2.4GHz"
#define WIFI_PASSWORD "wgmoos123"
#define WIFI_RECONNECT_DELAY 500

#define WAIT_BEFORE_SETUP 2000

#define MAIN_LOOP_DELAY 1000

#define NTP_SERVER "europe.pool.ntp.org"
#define NTP_UPDATE_INTERVAL 60000 // update interval in milliseconds
//#define NTP_OFFSET 3600 // offset to UTC, although that is not too smart without handling daylight saving time.
#define NTP_OFFSET 0 // UTC (no offset)

// 115200 because bootloader (or whatever) also sends at this rate
#define BAUDRATE 115200

// write the current timestamp every x milliseconds into a file
//#define WRITE_TIMESTAMP_INTERVAL 60000 // every 1 minute
#define WRITE_TIMESTAMP_INTERVAL 300000 // every 5 minutes

#define MQTT_SERVER "broker.hivemq.com" // 18.194.67.1
#define MQTT_PORT 1883
#define MQTT_CLIENT_PREFIX "DEBUGLEVEL-"
#define MQTT_RECONNECT_DELAY 5000
#define MQTT_PING_INTERVAL 5000
#define MQTT_TOPIC_PREFIX "debuglevel/"

#define MQTT_MAXIMUM_PACKET_SIZE 10240

#endif //HELLOWORLDARDUINO_CONFIG_H
