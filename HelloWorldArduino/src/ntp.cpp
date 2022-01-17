#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "config.h"
#include "ntp.h"

WiFiUDP ntpUDP;

NTPClient ntpClient(ntpUDP, NTP_SERVER, NTP_OFFSET, NTP_UPDATE_INTERVAL);

// see https://github.com/arduino-libraries/NTPClient/issues/29
#define LEAP_YEAR(Y) ((Y > 0) && !(Y % 4) && ((Y % 100) || !(Y % 400)))

/**
 * Gets the current date and time as ISO string.
 */
String getFormattedDateTime() {
    unsigned long rawTime = (ntpClient.getEpochTime()) / 86400L; // in days
    unsigned long days = 0, year = 1970;
    uint8_t month;
    static const uint8_t monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while ((days += (LEAP_YEAR(year) ? 366 : 365)) <= rawTime) {
        year++;
    }

    rawTime -= days - (LEAP_YEAR(year) ? 366 : 365); // now it is days in this year, starting at 0
    days = 0;
    for (month = 0; month < 12; month++) {
        uint8_t monthLength;
        if (month == 1) {
            // february
            monthLength = LEAP_YEAR(year) ? 29 : 28;
        } else {
            monthLength = monthDays[month];
        }

        if (rawTime < monthLength) {
            break;
        }

        rawTime -= monthLength;
    }

    String monthStr = ++month < 10 ? "0" + String(month) : String(month);     // jan is month 1
    String dayStr = ++rawTime < 10 ? "0" + String(rawTime) : String(rawTime); // day of month
    return String(year) + "-" + monthStr + "-" + dayStr + "T" + ntpClient.getFormattedTime() + "Z";
}

/**
 * Sets up NTP.
 * TODO: Does not work sometimes; missing error handling?
 */
void ntp_setup() {
    Serial.println("NTP | Setting up...");
    Serial.println("NTP | Begin...");
    ntpClient.begin();

    Serial.println("NTP | Updating...");
    ntpClient.update();

    Serial.printf("NTP | Set up: %s\n", getFormattedDateTime().c_str());
}

/**
 * Not used?
 * TODO: should be used; maybe not with the annoying Serial things
 */
void ntp_loop() {
    Serial.println("NTP | Updating...");
    // update() checks if the update interval has been reached; but has to be called manually nevertheless.
    ntpClient.update();
    Serial.println("NTP | Updated");
}

/**
 * Prints the current date and time.
 */
void ntp_printDateTime() {
    Serial.printf("NTP | Current Datetime: %s\n", getFormattedDateTime().c_str());
}