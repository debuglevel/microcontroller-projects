#include <Arduino.h>

#include "OneWire.h"
#include <DallasTemperature.h>
#include <ArduinoLog.h>

// This works with:
// https://randomnerdtutorials.com/esp32-ds18b20-temperature-arduino-ide/
// 38 pins board: https://raw.githubusercontent.com/AchimPieters/esp32-homekit-camera/master/Images/ESP32-38%20PIN-DEVBOARD.png (use pin G4)

// Data wire is plugged into GPIO 4 on the Arduino/ESP32
#define ONE_WIRE_BUS 4

// Comment out when using Arduino IDE Plotter
//#define PRINT_COUNT
// Comment in when only using logging instead of a single data line output.
//#define PRINT_DATA

#define RESOLUTION 9 // 9 to 12

#define DELAY 10

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup(void)
{
    // Start serial port
    Serial.begin(115200);

    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    // Log.begin(LOG_LEVEL_FATAL, &Serial);

    Log.noticeln("Dallas Temperature (adapted by debuglevel)");

    // This lines just make it so you can plug a DS18B20 directly into digitial pins 8-10.
    // (Without 4.7kOhm pull-up resistor; This probably only works on an Arduino, not on ESP32 et cetera.)
    // digitalWrite(1, LOW);
    // pinMode(1, OUTPUT);
    // digitalWrite(2, LOW);
    // pinMode(2, OUTPUT);
}

void loop(void)
{
    Log.traceln("Beginning loop...");

    DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

    // For testing purposes, reset the bus every loop so we can see if any devices appear or fall off
    Log.traceln("sensors.begin()... ");
    sensors.begin();
    Log.traceln("sensors.begin()... done");

    Log.traceln("Setting resolution to %d... ", RESOLUTION);
    sensors.setResolution(RESOLUTION);
    Log.traceln("Setting resolution to %d... done", RESOLUTION);

    // Get devices count on the wire
    Log.traceln("Getting devices count...: ");
    int numberOfDevices; // Number of temperature devices found
    numberOfDevices = sensors.getDeviceCount();
    Log.traceln("Getting devices count...: %d", numberOfDevices);

#ifdef PRINT_COUNT
    Serial.print("Count:");
    Serial.print(numberOfDevices, DEC);
    Serial.print(" ");
#endif PRINT_COUNT

    Log.traceln("Getting parasite mode...");
    bool isParasiteMode = sensors.isParasitePowerMode();
    Log.traceln("Getting parasite mode... done: %T", isParasiteMode);

    // report parasite power requirements

    Log.traceln("Requesting temperatures... ");
    sensors.requestTemperatures(); // Send the command to get temperatures
    Log.traceln("Requesting temperatures... done");

    // Loop through each found device
    Log.traceln("Looping %d devices...", numberOfDevices);
    for (int i = 0; i < numberOfDevices; i++)
    {
        Log.traceln("Looping device #%d...", i + 1);

        // Search the wire for address
        Log.traceln("Getting device address...: ");
        bool gotAddress = sensors.getAddress(tempDeviceAddress, i);
        // TODO: %x or %X only print the first part of the address. Add a function to return the whole thing as string/char[]
        Log.traceln("Getting device address... done: %T / %S", gotAddress, tempDeviceAddress);

        if (gotAddress)
        {
            Log.traceln("Getting temperature...");
            float temperature = sensors.getTempC(tempDeviceAddress);
            Log.traceln("Getting temperature... done: %F", temperature);

#ifdef PRINT_DATA
            // Some variants to identify sensors

            //// Print device address
            // printDeviceAddress(tempDeviceAddress);

            //// Print device index
            Serial.print("#");
            Serial.print(i, DEC);

            //// Print device index
            // Serial.print("Sensor");
            // Serial.print(i, DEC);

            // Print value separator
            Serial.print(":");
            Serial.print(temperature);

            // Print value separator (Arduino IDE Plotter also accepts comma)
            Serial.print(" ");
#endif PRINT_DATA
        }
        else
        {
            // else ghost device! Check your power requirements and cabling
            Log.warningln("Ghost device!");
        }
    }
    Log.traceln("Looped %d devices", numberOfDevices);

#ifdef PRINT_DATA
    Serial.println("");
#endif PRINT_DATA

    // Sensors need a certain delay (do they? or would they just block and we do not really need it here?)
    Log.traceln("Waiting for %d ms... ", DELAY);
    delay(DELAY);
    Log.traceln("Waiting for %d ms... done", DELAY);

    Log.traceln("Ended loop");
}

void printDeviceAddress(DeviceAddress deviceAddress)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (deviceAddress[i] < 16)
        {
            Serial.print("0");
        }

        Serial.print(deviceAddress[i], HEX);
    }
}