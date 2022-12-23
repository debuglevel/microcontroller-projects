# Sleep Motion Detector

Die grundlegende Idee ist, einen Sensor ans Bett zu schrauben um Bewegungen zu messen.
Da die Datenmenge sehr schnell sehr groß werden dürfte, ist es vermutlich sinnvoll das irgendwie zu aggregieren (z.B. Summe in Buckets von N-Sekunden o.ä.).

## Evaluation

### Sensoren

Vorhanden waren bei der Evaluation folgende Sensoren:

- ADXL345 (GY-291)
  - digitaler Output (SPI, I²C)
- ADXL335 (GY-61)
  - analoger Output
- MPU6050 (GY-521)

<https://www.seeedstudio.com/blog/2019/11/26/adxl356-get-started-adxl345-and-adxl335-comparison-guide/>

### MPU6050

Getestet mit `mpu_accel_simpel.c` und der Verdrahtung aus <https://randomnerdtutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/>.

Wenn man den Sensor plan auf den Tisch legt, springen X und Y zwischen Maximum und 0 hin und her, was das etwas anstrengend zu benutzen macht.
Sinnvoller ist erstmal Z.
Die Baseline ist circa zwischen 16800 und 17600.
Wenn man leicht auf den Tisch klopft ist es kurz zwischen circa 15000 und 20000.

Man sollte hier also halbwegs gut eine Baseline aufzeichnen können und dann Abweichungen davon feststellen können.
