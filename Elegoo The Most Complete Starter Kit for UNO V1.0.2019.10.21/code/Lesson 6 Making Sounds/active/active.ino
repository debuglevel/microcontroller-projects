//www.elegoo.com
//2016.12.08

int buzzer = 12;//the pin of the active buzzer

void setup()
{
  pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
  digitalWrite(buzzer, LOW);
}

void loop()
{
  return; 
  
  unsigned char i;
  while (1)
  {
    

    
    //output an frequency
    for (i = 0; i < 600; i++)
    {
      digitalWrite(buzzer, HIGH);
      delay(0.5);//wait for 1ms
      digitalWrite(buzzer, LOW);
      delay(0.5);//wait for 1ms
    }
    
    //output another frequency
    for (i = 0; i < 200; i++)
    {
      digitalWrite(buzzer, HIGH);
      delay(2);//wait for 2ms
      digitalWrite(buzzer, LOW);
      delay(2);//wait for 2ms
    }

        //output another frequency
    for (i = 0; i < 200; i++)
    {
      digitalWrite(buzzer, HIGH);
      delay(2);//wait for 2ms
      digitalWrite(buzzer, LOW);
      delay(3);//wait for 2ms
    }
  }
}
