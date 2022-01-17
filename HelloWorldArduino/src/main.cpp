#include <Arduino.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "pi.h"
#include "wifi.h"

uint32_t counter = 0;

void setup() {
    // put your setup code here, to run once:

    // 74880 because bootloader (or whatever) also sends at this rate
    Serial.begin(74880);

    Serial.println("======================================");
    Serial.println("Main.Setup | Setting up...");

    wifi_list();
    wifi_setup();
    //wifi_checkInternetConnection();

    Serial.println("Main.Setup | Setup done");
}


void loop() {
    // put your main code here, to run repeatedly:
    Serial.println("Main.Loop | Entering main loop...");

    Serial.print("Hello World! Loops since last reset: ");
    Serial.println(counter);

    delay(1000);
    counter += 1;

    // some silly calculation
    computePi();

    Serial.println("Main.Loop | Main loop finished");
}

