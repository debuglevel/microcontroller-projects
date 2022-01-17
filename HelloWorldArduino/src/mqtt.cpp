#include <PubSubClient.h>
#include <Arduino.h>
#include "config.h"
#include "mqtt.h"
#include <ESP8266WiFi.h>

const char *mqtt_server = MQTT_SERVER;
const int mqtt_port = MQTT_PORT;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
ulong lastMessageTime = 0;
uint16_t loopCount = 0;

String clientId;

/**
 * Sets up MQTT
 */
void mqtt_setup() {
    Serial.println("MQTT | Setting up...");

    Serial.printf("MQTT | Setting server '%s', port '%d'...\n", mqtt_server, mqtt_port);
    mqttClient.setServer(mqtt_server, mqtt_port);

    Serial.println("MQTT | Setting callback...");
    mqttClient.setCallback(mqtt_callback);

    Serial.println("MQTT | Set up");
}

void mqtt_callback(char *topic, byte *payload, unsigned int length) {
    Serial.printf("MQTT | Message arrived on topic '%s':", topic);

    for (uint i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
}

void mqtt_loop() {
    Serial.println("MQTT | Entering loop...");

    if (!mqttClient.connected()) {
        mqtt_reconnect();
    }
    mqttClient.loop();

    mqtt_send_ping();

    Serial.println("MQTT | Ended loop");
}

void mqtt_send_ping() {
    // Serial.println("MQTT | Sending ping message...");

    long now = millis();
    if (now - lastMessageTime > MQTT_PING_INTERVAL) {
        lastMessageTime = now;
        ++loopCount;

        char message[50];
        snprintf(message, 50, "Ping from %s loop #%hu", clientId.c_str(), loopCount);
        Serial.printf("MQTT | Publishing message: %s\n", message);
        mqttClient.publish("debuglevel/ping", message);
    }

    // Serial.println("MQTT | Sent ping message");
}

void mqtt_reconnect() {
    // Loop until MQTT is reconnected
    while (!mqttClient.connected()) {
        Serial.println("MQTT | Not connected to MQTT server; connecting to MQTT server...");

        // The client ID must be unique; a client with the same ID can only connect if it was disconnected before
        Serial.println("MQTT | Creating random client ID...");
        clientId = MQTT_CLIENT_PREFIX + String(random(0xffff), HEX);
        Serial.printf("MQTT | Using client ID=%s\n", clientId.c_str());

        Serial.println("MQTT | Connecting to server...");
        bool success = mqttClient.connect(clientId.c_str());
        Serial.printf("MQTT | Connection to server success: %d\n", success);

        if (success) {
            Serial.println("MQTT | Connected to MQTT server");

            // Publish an announcement
            String msg = "Client ID " + clientId + " connected to broker";
            mqttClient.publish("debuglevel/connect", msg.c_str());

            // Resubscribe
            mqttClient.subscribe("MAKO_inTopic");
        } else {
            Serial.printf("MQTT | Connecting failed, rc=%d\n", mqttClient.state());
            Serial.printf("MQTT | Waiting for %ims before retrying...", MQTT_RECONNECT_DELAY);
            delay(MQTT_RECONNECT_DELAY);
        }
    }
}

