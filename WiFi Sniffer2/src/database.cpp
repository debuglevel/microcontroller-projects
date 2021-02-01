// #include <stdio.h>
// #include <stdlib.h>
// #include <sqlite3.h>
// #include <vfs.h>
// #include <SPI.h>
// #include <FS.h>

// extern "C"
// {
// #include "user_interface.h"
// }

// #include <ESP8266WiFi.h>

// const char *data = "Callback function called";
// static int callback(void *data, int argc, char **argv, char **azColName)
// {
//     int i;
//     Serial.printf("%s: ", (const char *)data);
//     for (i = 0; i < argc; i++)
//     {
//         Serial.printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//     }
//     Serial.printf("\n");
//     return 0;
// }

// int db_open(const char *filename, sqlite3 **database)
// {
//     int returncode = sqlite3_open(filename, database);
//     if (returncode)
//     {
//         Serial.printf("Can't open SQLite database: %s\n", sqlite3_errmsg(*database));
//         return returncode;
//     }
//     else
//     {
//         Serial.printf("SQLite database opened successfully\n");
//     }

//     return returncode;
// }

// char *zErrorMessage = 0;
// int db_exec(sqlite3 *database, const char *sqlQuery)
// {
//     Serial.printf("SQL query: %s\n", sqlQuery);

//     long start = micros();
//     int returncode = sqlite3_exec(database, sqlQuery, callback, (void *)data, &zErrorMessage);
//     if (returncode != SQLITE_OK)
//     {
//         Serial.printf("SQL error: %s\n", zErrorMessage);
//         sqlite3_free(zErrorMessage);
//     }
//     else
//     {
//         Serial.printf("SQL Operation done successfully\n");
//     }

//     Serial.print(F("SQL time taken:"));
//     Serial.println(micros() - start);

//     return returncode;
// }

// void db_setup()
// {
//     //system_update_cpu_freq(SYS_CPU_160MHZ);

//     if (!SPIFFS.begin())
//     {
//         Serial.println("Failed to mount file system");
//         return;
//     }

//     // list SPIFFS contents
//     Dir dir = SPIFFS.openDir("/");
//     while (dir.next())
//     {
//         String fileName = dir.fileName();
//         size_t fileSize = dir.fileSize();
//         Serial.printf("FS File: %s, size: %ld\n", fileName.c_str(), (long)fileSize);
//     }
//     Serial.printf("\n");

//     // remove existing file
//     SPIFFS.remove("/test1.sqlite");

//     sqlite3_initialize();

//     // Open databases
//     File database_file_object;
//     vfs_set_spiffs_file_obj(&database_file_object);
//     sqlite3 *database;
//     if (db_open("/FLASH/test1.sqlite", &database))
//     {
//         return;
//     }

//     int returncode;
//     returncode = db_exec(database, "CREATE TABLE test1 (id INTEGER, content);");
//     if (returncode != SQLITE_OK)
//     {
//         sqlite3_close(database);
//         return;
//     }

//     returncode = db_exec(database, "INSERT INTO test1 VALUES (1, 'Hello, World from test1');");
//     if (returncode != SQLITE_OK)
//     {
//         sqlite3_close(database);
//         return;
//     }

//     returncode = db_exec(database, "SELECT * FROM test1");
//     if (returncode != SQLITE_OK)
//     {
//         sqlite3_close(database);
//         return;
//     }

//     sqlite3_close(database);
// }
