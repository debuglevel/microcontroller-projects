#include <ESP8266WiFi.h>
//#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
#include "config.h"

const char *wifi_ssid = WIFI_SSID;
const char *wifi_password = WIFI_PASSWORD;

/*
const char *mqtt_server = "broker.hivemq.com";
//const char *mqtt_server = "18.194.67.1";
const int mqtt_port = 1883;*/

//WiFiClient wifiClient;
//PubSubClient mqttClient(wifiClient);
//long lastMessageTime = 0;
//int value = 0;

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

    Serial.printf("WiFi | Connected with IP %s\n", WiFi.localIP().toString().c_str());
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

/*
void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    Serial.printf("MQTT: Message arrived on topic '%s':", topic);

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    // // Switch on the LED if an 1 was received as first character
    // if ((char)payload[0] == '1')
    // {
    //     digitalWrite(BUILTIN_LED, LOW); // Turn the LED on (Note that LOW is the voltage level
    //                                     // but actually the LED is on; this is because
    //                                     // it is active low on the ESP-01)
    // }
    // else
    // {
    //     digitalWrite(BUILTIN_LED, HIGH); // Turn the LED off by making the voltage HIGH
    // }
}

void mqtt_reconnect()
{
    // Loop until we're reconnected
    while (!mqttClient.connected())
    {
        Serial.println("MQTT: Connecting to MQTT server...");

        // Create a random client ID
        String mqttClientId = "WIFI-MQTT-";
        mqttClientId += String(random(0xffff), HEX);
        Serial.print("MQTT: Using clientID=");
        Serial.println(mqttClientId);

        // Attempt to connect
        if (mqttClient.connect(mqttClientId.c_str()))
        {
            Serial.println("MQTT: Connected to MQTT server");

            // Once connected, publish an announcement...
            mqttClient.publish("MAKO_outTopic", "Hello World, I was just set up");

            // ... and resubscribe
            mqttClient.subscribe("MAKO_inTopic");
        }
        else
        {
            Serial.printf("MQTT: Connecting failed, rc=%d\n", mqttClient.state());
            Serial.println("MQTT: Waiting for 5 secconds before retyring...");
            delay(5000);
        }
    }
}

void mqtt_setup()
{
    Serial.println("MQTT: Setting up...");
    Serial.printf("MQTT: Using server '%s', port '%d'\n", mqtt_server, mqtt_port);
    mqttClient.setServer(mqtt_server, mqtt_port);
    mqttClient.setCallback(mqtt_callback);
    Serial.println("MQTT: Set up");
}

void xxx_setup()
{
    //pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
    //Serial.begin(115200);

    wifi_setup();
    mqtt_setup();
}

void mqtt_loop()
{
    if (!mqttClient.connected())
    {
        Serial.println("MQTT: Not connected; connecting...");
        mqtt_reconnect();
    }
    mqttClient.loop();

    long now = millis();
    if (now - lastMessageTime > 2000)
    {
        lastMessageTime = now;
        ++value;

        char mqttMessage[50];
        snprintf(mqttMessage, 50, "Hello World from loop #%ld", value);
        Serial.printf("MQTT: Publishing message: %s\n", mqttMessage);
        mqttClient.publish("MAKO_outTopic", mqttMessage);
    }
}
 */