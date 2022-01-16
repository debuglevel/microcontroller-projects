
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

 // NB: use uintXX_t instead of int, long et cetera, because their length varies depending of the platform.
 uint32_t iterations;
 //iterations = 4294967295;
 //iterations = 1000000; // 1 million takes about 35,566 seconds on ESP8266 of the wemos d1 board. (28117 per second)
 iterations = 28117*0.2;

 Serial.print("PI | Using iterations = ");
 Serial.println(iterations);

 Serial.print("PI | Doing calculation rounds... ");
 uint32_t iteration;
 uint32_t count = 0;
 double x, y, z;
 for(iteration = 0; iteration < iterations; ++iteration) {
     x = (double)rand() / RAND_MAX;
     y = (double)rand() / RAND_MAX;
     z = x*x + y*y;

     if (z <= 1) {
       count++;
     }

     yield();
 }
 Serial.println("done");

 Serial.print("PI | Final calculation... ");
 double pi;
 pi = (double)count / iterations * 4;
 Serial.print("done: ");

 Serial.println(pi, 10);

 Serial.println("PI | Computed pi...");
}
