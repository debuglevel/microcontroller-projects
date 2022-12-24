/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Simple Accelerometer Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/


#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);

//   while (!Serial)
//     delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
        Serial.println("+-2G");
        break;
    case MPU6050_RANGE_4_G:
        Serial.println("+-4G");
        break;
    case MPU6050_RANGE_8_G:
        Serial.println("+-8G");
        break;
    case MPU6050_RANGE_16_G:
        Serial.println("+-16G");
        break;
  }

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
        Serial.println("+- 250 deg/s");
        break;
    case MPU6050_RANGE_500_DEG: //
        Serial.println("+- 500 deg/s");
        break;
    case MPU6050_RANGE_1000_DEG:
        Serial.println("+- 1000 deg/s");
        break;
    case MPU6050_RANGE_2000_DEG:
        Serial.println("+- 2000 deg/s");
        break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
        Serial.println("260 Hz");
        break;
    case MPU6050_BAND_184_HZ:
        Serial.println("184 Hz");
        break;
    case MPU6050_BAND_94_HZ:
        Serial.println("94 Hz");
        break;
    case MPU6050_BAND_44_HZ:
        Serial.println("44 Hz");
        break;
    case MPU6050_BAND_21_HZ:
        Serial.println("21 Hz");
        break;
    case MPU6050_BAND_10_HZ:
        Serial.println("10 Hz");
        break;
    case MPU6050_BAND_5_HZ: //
        Serial.println("5 Hz");
        break;
  }

  // set/getCycleRate

  Serial.println("");
  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
//   Serial.print("Acceleration X: ");
//   Serial.print(a.acceleration.x);
//   Serial.print(", Y: ");
//   Serial.print(a.acceleration.y);
//   Serial.print(", Z: ");
  //Serial.print(a.acceleration.z);
//   Serial.println(" m/s^2");

//   Serial.print("Rotation X: ");
//   Serial.print(g.gyro.x);
//   Serial.print(", Y: ");
//   Serial.print(g.gyro.y);
//   Serial.print(", Z: ");
//   Serial.print(g.gyro.z);
//   Serial.println(" rad/s");

//   Serial.print("Temperature: ");
//   Serial.print(temp.temperature);
//   Serial.println(" degC");

//   Serial.println("");
//   delay(500);



    //a.acceleration.z;

    //Vector rawAccel = mpu.readRawAccel();
    //Vector normAccel = mpu.readNormalizeAccel();

    // Serial.print("Xraw:");
    // Serial.print(rawAccel.XAxis);
    // Serial.print(" Yraw:");
    // Serial.print(rawAccel.YAxis);
    Serial.print(" Zraw:");
    //Serial.print(rawAccel.ZAxis);
    Serial.print(a.acceleration.z);

    //  Serial.print(" Xnorm:");
    //  Serial.print(normAccel.XAxis);
    //  Serial.print(" Ynorm:");
    //  Serial.print(normAccel.YAxis);
    //  Serial.print(" Znorm:");
    //  Serial.println(normAccel.ZAxis);

    Serial.println();

    delay(100);
}