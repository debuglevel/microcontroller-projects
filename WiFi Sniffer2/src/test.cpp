#include <Arduino.h>
//#include "ESP8266TrueRandom.h"
#include "test.h"
#include "random.h"

// void printRandom()
// {
//     // byte uuidNumber[16]; // UUIDs in binary form are 16 bytes long
//     // ESP8266TrueRandom.uuid(uuidNumber);
//     // String uuidStr = ESP8266TrueRandom.uuidToString(uuidNumber);
//     // Serial.println("==== The UUID number is " + uuidStr);

//     // Use an old-school array
//     uint8_t uuid_array[16];
//     ESPRandom::uuid(uuid_array);
//     Serial.println("==== The X UUID number is " + ESPRandom::uuidToString(uuid_array));
// }