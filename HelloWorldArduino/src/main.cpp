
#include <Arduino.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define SEED time(NULL)

// Declare functions below cecause C++ is annoying.
void computePi();

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

  Serial.print("Hello World! Loops since last reset: ");
  Serial.println(counter);

  delay(1000);
  counter += 1;

// some silly calculation
//  computePi();
}


void computePi() {
 Serial.println("PI | Computing pi...");

 Serial.print("PI | Using seed = ");
 Serial.println(SEED);
 srand(SEED); // uses uptime seconds (integer) as seed

 uint iterations, i, count;
 double x, y, z, pi;

 // TODO: not sure how big an int here is.
 // TODO: seems to crash on later loop calls if too big. no idea why.
 iterations = 52000;

 Serial.print("PI | Using iterations = ");
 Serial.println(iterations);

 count = 0;

 Serial.print("PI | Doing calculation rounds... ");
 for(i = 0; i < iterations; ++i) {
     //Serial.print("1..");
     x = (double)rand() / RAND_MAX;
     //Serial.print("2..");
     y = (double)rand() / RAND_MAX;
     //Serial.print("3..");
     z = x*x + y*y;
     //Serial.print("4..");

     if (z <= 1) {
       //Serial.print("5..");
       count++;
     }
     //Serial.print("6..");
 }
 Serial.println("done");

 Serial.print("PI | Final calculation... ");
 pi = (double) count / iterations * 4;
 //pi = (double)((count/iterations)*4);
 Serial.print("done: ");

 Serial.println(pi);

 Serial.println("PI | Computed pi...");
}
