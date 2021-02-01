#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:

  // 74880 because boatloader (or whatever) also sends at this rate
  Serial.begin(74880);
}

void loop()
{
  // put your main code here, to run repeatedly:

  Serial.println("Hello World");
  delay(1000);
}