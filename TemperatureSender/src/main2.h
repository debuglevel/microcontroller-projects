#include <DallasTemperature.h>
void printAddress(DeviceAddress deviceAddress);
void printTemperature(DeviceAddress deviceAddress);
void printAlarms(uint8_t deviceAddress[]);
void printData(DeviceAddress deviceAddress);
void checkAlarm(DeviceAddress deviceAddress);