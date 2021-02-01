#include "upload.h"
#include <ESP8266HTTPClient.h>
#include <FS.h>
#include "config.h"
#include "fileDatabase.h"
#include <ArduinoJson.h>

//#define POST_URL "http://ip172-18-0-51-bos96b033cq000bd1eq0-5984.direct.labs.play-with-docker.com/wifisniffer"
#define POST_URL "http://envk1jke6tb9.x.pipedream.net"

class FakeStream : public Stream
{
protected:
    size_t fakesize;

public:
    FakeStream(size_t size) : fakesize(size) {}

    virtual int available()
    {
        return fakesize;
    }
    virtual int read()
    {
        if (fakesize)
        {
            --fakesize;
            return 0x5a;
        }
        return -1;
    }
    virtual int peek()
    {
        return 0x5a;
    }
    virtual void flush()
    {
        fakesize = 0;
    };
    virtual size_t write(uint8_t data)
    {
        (void)data;
        return 1;
    }
    size_t size()
    {
        return fakesize;
    }
    const char *name()
    {
        return "5a";
    }
};

void transfer_file()
{
    Serial.println("UPLOAD: Transferring file...");

    File jsonFile = fdb_openStream(WIFIDEVICES_FILE_JSON, "r");

    const size_t capacity = JSON_OBJECT_SIZE(2) + 20;
    DynamicJsonDocument jsonDocument(capacity);

    while (deserializeJson(jsonDocument, jsonFile))
    {
        Serial.println("UPLOAD: Found another JSON document");

        HTTPClient http;
        http.begin(POST_URL);

        Serial.println("UPLOAD: Serialising JSON for HTTP body...");
        String jsonString;
        serializeJson(jsonDocument, jsonString);

        http.addHeader("Content-Type", "application/json");
        http.addHeader("Content-Length", String(jsonString.length()));

        Serial.println("UPLOAD: POSTing...");
        int httpCode = http.POST(jsonString);
        Serial.printf("UPLOAD: HTTP request returned code %d\n", httpCode);

        http.end();
    }
    jsonFile.close();

    Serial.println("Transferred file");
}