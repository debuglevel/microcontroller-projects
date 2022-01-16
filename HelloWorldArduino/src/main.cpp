#include <Arduino.h>

uint counter = 0;

void setup()
{
  // put your setup code here, to run once:

  // 74880 because boatloader (or whatever) also sends at this rate
  Serial.begin(74880);
}


void loop()
{
  // put your main code here, to run repeatedly:

  Serial.print("Hello World! Seconds since last reset: ");
  Serial.println(counter);

  delay(1000);
  counter += 1;
}
