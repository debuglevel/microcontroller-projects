#include <Arduino.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "pi.h"
#include "wifi.h"
#include "misc.h"
#include "config.h"
#include "random.h"
#include "ntp.h"
#include "filedatabase.h"
#include "mqtt.h"
#include "sensors.h"

uint32_t counter = 1;

/**
 * Runs once on microcontroller reset.
 */
void setup()
{
    waitSetup();

    Serial.begin(BAUDRATE);

    Serial.println("======================================");
    Serial.println("Main.Setup | Setting up...");

    Serial.print("Main.Setup | Baud rate was already set to: ");
    Serial.println(BAUDRATE);

    wifi_list();
    wifi_setup();
    // wifi_checkInternetConnection();

    ntp_setup();

    mqtt_setup();

    //fdb_setup();
    //fdb_list("");
    //write_timestamp_to_fdb();

    set_seed_to_uptime();

    Serial.println("Main.Setup | Setup done");
}

/**
 * Runs repeatedly.
 */
void loop()
{
    ulong start_time = millis();
    Serial.printf("Main.Loop | Entering main loop, iteration %u...\n", counter);

    publish_sensor_data();
    // wifi_list();
    //  Serial.print("Hello World!");

    // some silly calculation
    // computePi();

    Serial.println("Main.Loop | Doing maintenance...");
    periodically_write_timestamp_to_fdb();
    mqtt_loop();
    ntp_loop();

    Serial.printf("Main.Loop | Delaying for %ums...\n", MAIN_LOOP_DELAY);
    delay(MAIN_LOOP_DELAY);

    ulong loop_time = millis() - start_time;
    Serial.printf("Main.Loop | Main loop finished, iteration %u, took %lums...\n", counter, loop_time);
    counter += 1;
}
