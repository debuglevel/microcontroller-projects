#include <Arduino.h>

/**
 * This might be an useful method if some action before
 * took an unclear amount of time (e.g. connecting to a WiFi)
 *
 * But this might also be okay to be used e.g. on Wemos D1 ESP8266,
 * without connecting to WiFi, as it seems to take different durations
 * to enter setup().
 */
void set_seed_to_uptime() {
    unsigned long seed = micros();
    Serial.printf("Random | Using uptime %luµs as randomSeed(%lu)...\n", seed, seed);
    randomSeed(seed);
}