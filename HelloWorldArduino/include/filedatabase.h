#ifndef HELLOWORLDARDUINO_FILEDATABASE_H
#define HELLOWORLDARDUINO_FILEDATABASE_H

#include <FS.h>

void fdb_setup();

void fdb_list(const char *directory);

void fdb_read(const char *filename);

void fdb_write(const char *filename, const char *line);

File fdb_openStream(const char *filename, const char *mode);

#endif //HELLOWORLDARDUINO_FILEDATABASE_H
