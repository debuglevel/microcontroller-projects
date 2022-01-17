#ifndef HELLOWORLDARDUINO_CONFIG_H
#define HELLOWORLDARDUINO_CONFIG_H

#define WIFI_SSID "Pretty Fly For a WiFi 2.4GHz"
#define WIFI_PASSWORD "SECRET"
#define WIFI_RECONNECT_DELAY 500

#define WAIT_BEFORE_SETUP 2000

#define MAIN_LOOP_DELAY 1000

#define NTP_SERVER "europe.pool.ntp.org"
#define NTP_UPDATE_INTERVAL 60000 // update interval in milliseconds
//#define NTP_OFFSET 3600 // offset to UTC, although that is not too smart without handling daylight saving time.
#define NTP_OFFSET 0 // UTC (no offset)

// 74880 because bootloader (or whatever) also sends at this rate
#define BAUDRATE 74880

#endif //HELLOWORLDARDUINO_CONFIG_H
