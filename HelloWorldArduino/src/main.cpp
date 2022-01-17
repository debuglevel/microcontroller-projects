#include <Arduino.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "pi.h"
#include "wifi.h"
#include "misc.h"
#include "config.h"

uint32_t counter = 0;

/**
 * Runs once on microcontroller reset.
 */
void setup() {
    waitSetup();

    Serial.begin(BAUDRATE);

    Serial.println("======================================");
    Serial.println("Main.Setup | Setting up...");

    Serial.print("Main.Setup | Baud rate was already set to: ");
    Serial.println(BAUDRATE);

    wifi_list();
    wifi_setup();
    //wifi_checkInternetConnection();

    Serial.println("Main.Setup | Setup done");
}

/**
 * Runs repeatedly.
 */
void loop() {
    Serial.println("Main.Loop | Entering main loop...");

    Serial.print("Hello World! Loops since last reset: ");
    Serial.println(counter);

    delay(1000);
    counter += 1;

    // some silly calculation
    computePi();

    Serial.println("Main.Loop | Main loop finished");
}

