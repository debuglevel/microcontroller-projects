#ifndef HELLOWORLDARDUINO_MISC_H
#define HELLOWORLDARDUINO_MISC_H

void waitSetup();

void write_timestamp_to_fdb();

void periodically_write_timestamp_to_fdb();

String get_unique_device_id();
#endif //HELLOWORLDARDUINO_MISC_H
