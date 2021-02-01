#ifndef FILEDATABASE_H_
#define FILEDATABASE_H_

#include <FS.h>

void fdb_setup();
void fdb_list(const char *directory);
void fdb_read(const char *filename);
void fdb_write(const char *filename, const char *line);
File fdb_openStream(const char *filename, const char *mode);

#endif