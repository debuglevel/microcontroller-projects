#ifndef HELLOWORLDARDUINO_MQTT_H
#define HELLOWORLDARDUINO_MQTT_H

void mqtt_setup();

void mqtt_callback(char *topic, byte *payload, unsigned int length);

void mqtt_loop();

void mqtt_reconnect();

void mqtt_send_ping();

void mqtt_send_message(const char *topic, const char *message);
#endif //HELLOWORLDARDUINO_MQTT_H
