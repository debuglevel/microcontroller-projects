#include <Arduino.h>
#include "wifiSniffer.h"
#include "fileDatabase.h"
#include <FS.h>
#include "wifi.h"
#include "ntp.h"
#include "upload.h"
#include "config.h"

void setup()
{
  Serial.begin(74880);
  Serial.println("====================");
  Serial.println("Main: Setting up...");

  fdb_setup();

  //SPIFFS.remove(WIFIDEVICES_FILE);

  //fdb_read(WIFIDEVICES_FILE_CSV);
  //fdb_read(WIFIDEVICES_FILE_JSON);
  fdb_read(WIFIDEVICES_FILE_MSGPACK);
  SPIFFS.remove(WIFIDEVICES_FILE_JSON);
  SPIFFS.remove(WIFIDEVICES_FILE_CSV);
  //SPIFFS.remove(WIFIDEVICES_FILE_MSGPACK);
  fdb_list("/");
  //fdb_write(WIFIDEVICES_FILE_CSV, "== This is a new start ==\n");

  wifi_list();
  //wifi_setup();
  //wifi_checkInternetConnection();

  ntp_setup();
  ntp_loop();

  //transfer_file();

  //mqtt_setup();

  wifisniffer_setup();

  Serial.println("Main: Set up");
}

void loop()
{
  delay(10);
  //ntp_printDateTime();
  //mqtt_loop();
}