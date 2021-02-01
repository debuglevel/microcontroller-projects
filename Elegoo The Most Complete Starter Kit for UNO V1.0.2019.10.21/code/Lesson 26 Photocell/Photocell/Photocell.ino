//www.elegoo.com
//2016.12.9

int lightPin = 0;
int latchPin = 11;
int clockPin = 9;
int dataPin = 12;
int ledPin = 3;

int leds = 0;

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);



  Serial.begin(115200);
}

void updateShiftRegister()
{
  //  digitalWrite(latchPin, LOW);
  //  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  //  digitalWrite(latchPin, HIGH);
}

void loop()
{
  // between 0 and 1023 (or 900 for a really bright light; 762 if white LED stands right next so sensor; 171 for my environmental light)
  int reading  = analogRead(lightPin);
  double brightnessMasured = (reading - 171.0) / (762.0 - 171.0);
    Serial.print("Measured: ");
    Serial.println(reading);


  //  int numLEDSLit = reading / 57;  //1023 / 9 / 2
  //
  //  if (numLEDSLit > 8)
  //  {
  //    numLEDSLit = 8
  //  };
  //
  //  leds = 0;   // no LEDs lit to start
  //
  //  for (int i = 0; i < numLEDSLit; i++)
  //  {
  //    leds = leds + (1 << i);  // sets the i'th bit
  //  }
  //
  //  updateShiftRegister();
  //delay(50);
}
