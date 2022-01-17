#include <Arduino.h>
#include "config.h"
#include "filedatabase.h"
#include "ntp.h"

/**
 * Wait a configured delay before entering setup.
 * Gives the development machine some time to connect the monitor.
 */
void waitSetup() {
    delay(WAIT_BEFORE_SETUP);
}

/**
 * Writes the current date and time to a file
 */
void write_timestamp_to_fdb() {
    String datetime = getFormattedDateTime().c_str();
    String filename = "last_datetime.txt";
    Serial.printf("Writing current date time '%s' into %s\n", datetime.c_str(), filename.c_str());
    fdb_write(filename.c_str(), datetime.c_str());
}

ulong last_write = 0;

/**
 * Writes the current date and time periodically to a file.
 */
void periodically_write_timestamp_to_fdb() {
    if (millis() - last_write >= WRITE_TIMESTAMP_INTERVAL) {
        last_write = millis();
        write_timestamp_to_fdb();
    }
}