#include <Arduino.h>
#include "config.h"

/**
 * Wait a configured delay before entering setup.
 * Gives the development machine some time to connect the monitor.
 */
void waitSetup() {
    delay(WAIT_BEFORE_SETUP);
}