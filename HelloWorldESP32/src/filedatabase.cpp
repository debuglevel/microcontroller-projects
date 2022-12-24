#include <FS.h>
#include <SPIFFS.h>
#include <dirent.h>

void fdb_setup() {
    Serial.println("FDB | Mounting SPIFFS...");
    bool success = SPIFFS.begin();

    if (success) {
        Serial.println("FDB | Mounted SPIFFS");
    } else {
        Serial.println("FDB | Failed to mount SPIFFS");
    }
}

// TODO: Untested
void fdb_list(const char *directory) {
    Serial.printf("FDB | Files in filesystem '%s':\n", directory);

    DIR* dir = opendir(directory);
    if (dir == NULL) {
        return;
    }

    while (true) {
        struct dirent* de = readdir(dir);
        if (!de) {
            break;
        }
        
        printf("FDB | Filename: %s\n", de->d_name);
    }
}

File fdb_openStream(const char *filename, const char *mode) {
    Serial.printf("FDB | Opening file '%s' in mode '%s'...\n", filename, mode);
    File file = SPIFFS.open(filename, mode);
    if (!file) {
        Serial.printf("FDB | Failed to open file '%s' in mode '%s'\n", filename, mode);
        return File();
    }

    return file;
}

void fdb_write(const char *filename, const char *buffer) {
    //ulong start_time = millis();

    size_t length = strlen(buffer);
    if (length == 0) {
        //Serial.println("FDB | Refusing to write 0 byte buffer");
        return;
    }

    File file = fdb_openStream(filename, "a");

    //Serial.printf("FDB | Writing to file '%s'...\n", filename);
    int bytesWritten = file.print(buffer);
    if (bytesWritten > 0) {
        //Serial.printf("FDB | Wrote %i bytes\n", bytesWritten);
    } else {
        Serial.printf("FDB | Writing file '%s' failed\n", filename);
    }

    //Serial.printf("FDB | Closing file '%s'...\n", filename);
    file.close();

    //Serial.printf("FDB | Writing took %lums...\n", millis() - start_time);
}

void fdb_read(const char *filename) {
    Serial.printf("FDB | Opening file '%s' for reading...\n", filename);
    File file = SPIFFS.open(filename, "r");
    if (!file) {
        Serial.println("FDB | Failed to open file for reading");
        return;
    }

    Serial.printf("FDB | File content of '%s':\n", filename);
    while (file.available()) {
        Serial.write(file.read());
    }

    Serial.printf("FDB | Closing file '%s'...\n", filename);
    file.close();
}
