//www.elegoo.com
//2018.12.19
#include <Servo.h>
Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(00);// move servos to center position -> 90°
  delay(3000);
  
}
void loop() {

  for (int i = 0; i<=10000; i++)
  {
    Serial.println(i);
    
    myservo.write(i);
    
    delay(40);
  }

  delay(3000);
}
