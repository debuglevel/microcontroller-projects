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
#include "wifi.h"
#include "mqtt.h"
#include "ntp.h"

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);




    wifi_list();
    wifi_setup();
    // wifi_checkInternetConnection();

    //ntp_setup();

    mqtt_setup();








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

  mpu.enableCycle(false);

  Serial.println("");
  delay(100);
}

typedef struct {
    float accelX;
    float accelY;
    float accelZ;
    float gyroX;
    float gyroY;
    float gyroZ;
} sensor_values_t;

// struct Gyro_data_structure
// {
//     //char command_name[6];
//     int gyro_X;
//     //int gyro_Y;
//     //int gyro_Z;
// };

// void writeBinary(sensors_event_t accel, sensors_event_t gyro) {
  
//   Serial.print("##");
//   Gyro_data_structure Gyro_data = {200};
//   Serial.print(sizeof(Gyro_data_structure)); // 4 bytes / 32 bit
//   Serial.print("::");
//   Serial.write((uint8_t *) &Gyro_data, sizeof Gyro_data);
//   Serial.print("##");
//   delay(100);


//   Serial.print(sizeof(float)); // 4 bytes / 32 bit
//   Serial.print("//");
//   float test = 1.23;
//   Serial.write((byte*)&test, sizeof(float));
//   Serial.print("\\\\");


//   sensor_values_t vals;
//   vals.accelX = 1.23; //accel.acceleration.x;
//   vals.accelY = 4.56; //accel.acceleration.y;
//   vals.accelZ = 7.89; //accel.acceleration.z;
//   vals.gyroX = 0.01; //gyro.gyro.x;
//   vals.gyroY = 0.001; //gyro.gyro.y;
//   vals.gyroZ = 0.0001; //gyro.gyro.z;


//   Serial.println("========");
//   Serial.println(sizeof(sensor_values_t));
//   Serial.println("--------");
  
//   Serial.write((byte*)&vals, sizeof(vals));

//   Serial.println("");
//   Serial.println("========");
// }

String getCsvLine(sensors_event_t accel, sensors_event_t gyro) {
  String msg = "" + String(accel.acceleration.x) + "," + accel.acceleration.y + "," + accel.acceleration.z + "," + gyro.gyro.x + "," + gyro.gyro.y + "," + gyro.gyro.z;
  return msg;
}

void writeMQTT(sensors_event_t accel, sensors_event_t gyro) {
  mqtt_send_message("sleepsensor", getCsvLine(accel, gyro));
}

void writeMQTT(String msg) {
  mqtt_send_message("sleepsensor", msg);
}

void writeCSV(sensors_event_t accel, sensors_event_t gyro) {
  Serial.print(accel.acceleration.x);
  Serial.print(",");
  Serial.print(accel.acceleration.y);
  Serial.print(",");
  Serial.print(accel.acceleration.z);
  Serial.print(",");

  Serial.print(gyro.gyro.x);
  Serial.print(",");
  Serial.print(gyro.gyro.y);
  Serial.print(",");
  Serial.print(gyro.gyro.z);

  Serial.println();
}

void writePlotter(sensors_event_t accel, sensors_event_t gyro) {
  Serial.print(" AccX:");
  Serial.print(accel.acceleration.x);
  Serial.print(" AccY:");
  Serial.print(accel.acceleration.y);
  Serial.print(" AccZ:");
  Serial.print(accel.acceleration.z);

  Serial.print(" GyroX:");
  Serial.print(gyro.gyro.x);
  Serial.print(" GyroY:");
  Serial.print(gyro.gyro.y);
  Serial.print(" GyroZ:");
  Serial.print(gyro.gyro.z);

  Serial.println();
}

void loop() {
  Serial.println("loop() | Begin");

  /* Get new sensor events with the readings */
  sensors_event_t accel, gyro, temperature;

  //mqtt_send_message("test1", "test2");

  mqtt_loop();

  String csvLines = "";
  for (int i = 0; i < 200; i++) {
    mpu.getEvent(&accel, &gyro, &temperature);
    String csvLine = getCsvLine(accel, gyro);
    // Note: each CSV line has a maximum size of 42 bytes:
    // "-10.55,-10.13,-10.46,-10.01,-10.04,-10.05n"
    // We have to consider this because the MQTT client has a maximum buffer size we cannot exceed (or have to increase it at least).
    // Current buffer size is 10240 bytes in which fit 243.8 CSV lines.
    csvLines += csvLine + "\n";
  }
  
  writeMQTT(csvLines);
  csvLines = "";

  //writeMQTT(accel, gyro);

  //writeBinary(accel, gyro);
  //writeCSV(accel, gyro);
  //writePlotter(accel, gyro);

  //Serial.println("loop() | Delay 100");
  //delay(100);

  //Serial.println("loop() | Delay 500");
  //delay(500);

  //Serial.println("loop() | Delay 5000");
  //delay(5000);
  
  //millis(1000);
  
  Serial.println("loop() | End");
}
