//www.elegoo.com
//2016.12.08
/*****************************************/
const int ledPin = 13;//the led attach to

void setup()
{
  pinMode(ledPin, OUTPUT); //initialize the ledPin as an output
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
}
/******************************************/
void loop()
{
  int digitalVal = digitalRead(2);
  
  if (digitalVal == LOW)
  {
    digitalWrite(ledPin, HIGH); //turn the led on
  }
  else
  {
    digitalWrite(ledPin, LOW); //turn the led off
  }
}
/**********************************************/
