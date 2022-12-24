#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

const char *wifi_ssid = WIFI_SSID;
const char *wifi_password = WIFI_PASSWORD;

/**
 * Sets up a WiFi connection.
 */
void wifi_setup() {
    Serial.println("WiFi | Setting up...");

    Serial.printf("WiFi | Connecting to SSID '%s'...\n", wifi_ssid);
    WiFi.begin(wifi_ssid, wifi_password);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.printf("WiFi | Still not connected. Delaying for %dms...\n", WIFI_RECONNECT_DELAY);
        delay(WIFI_RECONNECT_DELAY);
    }

    Serial.printf("WiFi | Connected as IP %s\n", WiFi.localIP().toString().c_str());
}

/**
 * Scans WiFi networks and lists them
 */
void wifi_list() {
    Serial.println("WiFi | Scanning for networks...");

    int8_t networksCount = WiFi.scanNetworks(false, true, 0, NULL);
    Serial.printf("WiFi | Found %d networks:\n", networksCount);

    for (int8_t i = 0; i < networksCount; i++) {
        Serial.printf("WiFi | Found network with SSID='%s' \t RSSI=%i Channel=%i\n",
                      WiFi.SSID(i).c_str(),
                      WiFi.RSSI(i),
                      WiFi.channel(i));
    }
}

/**
 * Checks the internet connection by issuing a HTTP request.
 * Seems to crash, though.
 */
void wifi_checkInternetConnection()
{
    Serial.println("WiFi | Checking internet connection...");
    Serial.print("WiFi | Status is ");
    Serial.println(WiFi.status());

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi | WiFi status is connected");

        Serial.println("WiFi | Checking connectivity via HTTP request...");

        const char *url = "http://api.ipify.org/";
        Serial.printf("WiFi | Requesting GET '%s'...\n", url);
        HTTPClient httpClient;
        WiFiClient wiFiClient;
        httpClient.begin(wiFiClient, url);
        int httpCode = httpClient.GET();
        Serial.printf("WiFi | Response on GET '%s': HTTP code %d\n", url, httpCode);

        if (httpCode > 0) {
            String payload = httpClient.getString();
            Serial.printf("WiFi | Response on GET '%s': Content: '%s'\n", url, payload.c_str());
        } else {
            Serial.printf("WiFi | Request on GET '%s' failed\n", url);
        }

        Serial.println("Ending HTTP Client...");
        httpClient.end();
        Serial.println("Ended HTTP Client");
    } else {
        Serial.println("WiFi | WiFi status is NOT connected");
    }

    // TODO: somehow crashes between end of inner if block and this instruction.
    Serial.println("WiFi | Checked internet connection");
}
