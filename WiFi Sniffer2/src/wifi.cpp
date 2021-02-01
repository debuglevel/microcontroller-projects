
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
#include "config.h"

const char *wifi_ssid = WIFI_SSID;
const char *wifi_password = WIFI_PASSWORD;
const char *mqtt_server = "broker.hivemq.com";
//const char *mqtt_server = "18.194.67.1";
const int mqtt_port = 1883;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
long lastMessageTime = 0;
int value = 0;

void wifi_setup()
{
    Serial.println("WIFI: Setting up...");
    Serial.printf("WIFI: Connecting to '%s'...\n", wifi_ssid);
    WiFi.begin(wifi_ssid, wifi_password);

    while (WiFi.status() != WL_CONNECTED)
    {
        int reconnectWait = 500;
        Serial.printf("WIFI: Still not connected. Waiting for %dms...\n", reconnectWait);
        delay(reconnectWait);
    }

    Serial.print("WIFI: Connected with IP ");
    Serial.println(WiFi.localIP());

    //Serial.println("IP address: ");
    //Serial.println(WiFi.localIP());

    unsigned long seed = micros();
    Serial.printf("WIFI: Setting randomSeed(%lu)...\n", seed);
    randomSeed(seed);
}

void wifi_list()
{
    Serial.println("WIFI: Scanning networks...");
    int networkCount = WiFi.scanNetworks();
    Serial.printf("WIFI: Scanned %d networks:\n", networkCount);

    for (int i = 0; i < networkCount; i++)
    {
        Serial.print("WIFI: Found network SSID='");
        Serial.print(WiFi.SSID(i));
        Serial.print("' RSSI=");
        Serial.println(WiFi.RSSI(i));
    }
}

void wifi_checkInternetConnection()
{
    Serial.println("WIFI: Checking internet connection...");
    Serial.print("WIFI: Status is ");
    Serial.println(WiFi.status());

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WIFI: WiFi status is connected; checking via HTTP request...");

        const char *url = "http://api.ipify.org/";
        Serial.printf("WIFI: Requesting HTTP: '%s'...\n", url);
        HTTPClient httpClient;
        httpClient.begin(url);
        int httpCode = httpClient.GET();
        Serial.printf("WIFI: Requested via HTTP '%s' with HTTP code %d\n", url, httpCode);

        if (httpCode > 0)
        {
            String payload = httpClient.getString();
            Serial.printf("WIFI: Requested HTTP '%s' content:", url);
            Serial.println(payload);
        }
        else
        {
            Serial.printf("WIFI: HTTP request '%s' failed\n", url);
        }

        httpClient.end();
    }
    else
    {
        Serial.println("WIFI: WiFi status is NOT connected");
    }
}

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