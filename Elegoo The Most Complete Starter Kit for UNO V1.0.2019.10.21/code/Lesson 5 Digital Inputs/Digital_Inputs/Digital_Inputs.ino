//www.elegoo.com
//2016.12.08

int ledPin = 6;
int buttonApin = 4;
int buttonBpin = 5;

byte leds = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Setting up...");
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  digitalWrite(ledPin, HIGH);
}

void loop()
{
  if (digitalRead(buttonApin) == LOW)
  {
    Serial.println("Pressed A");
    digitalWrite(ledPin, HIGH);
  }
  if (digitalRead(buttonBpin) == LOW)
  {
    Serial.println("Pressed B");
    digitalWrite(ledPin, LOW);
  }
}
