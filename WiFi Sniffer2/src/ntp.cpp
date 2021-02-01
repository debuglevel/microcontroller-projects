#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;

#define UPDATE_INTERVAL 60000 // update interval in milliseconds
#define NTP_SERVER "europe.pool.ntp.org"

NTPClient ntpClient(ntpUDP, NTP_SERVER, 0, UPDATE_INTERVAL);

// see https://github.com/arduino-libraries/NTPClient/issues/29
#define LEAP_YEAR(Y) ((Y > 0) && !(Y % 4) && ((Y % 100) || !(Y % 400)))
String getFormattedDateTime()
{
    unsigned long rawTime = (ntpClient.getEpochTime()) / 86400L; // in days
    unsigned long days = 0, year = 1970;
    uint8_t month;
    static const uint8_t monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while ((days += (LEAP_YEAR(year) ? 366 : 365)) <= rawTime)
    {
        year++;
    }

    rawTime -= days - (LEAP_YEAR(year) ? 366 : 365); // now it is days in this year, starting at 0
    days = 0;
    for (month = 0; month < 12; month++)
    {
        uint8_t monthLength;
        if (month == 1)
        {
            // february
            monthLength = LEAP_YEAR(year) ? 29 : 28;
        }
        else
        {
            monthLength = monthDays[month];
        }

        if (rawTime < monthLength)
        {
            break;
        }

        rawTime -= monthLength;
    }

    String monthStr = ++month < 10 ? "0" + String(month) : String(month);     // jan is month 1
    String dayStr = ++rawTime < 10 ? "0" + String(rawTime) : String(rawTime); // day of month
    return String(year) + "-" + monthStr + "-" + dayStr + "T" + ntpClient.getFormattedTime() + "Z";
}

void ntp_setup()
{
    Serial.println("NTP: Setting up...");
    ntpClient.begin();
    ntpClient.update();
    Serial.print("NTP: Set up: ");
    Serial.println(getFormattedDateTime());
}

void ntp_loop()
{
    ntpClient.update();
}

void ntp_printDateTime()
{
    Serial.print("NTP: ");
    Serial.println(getFormattedDateTime());
}