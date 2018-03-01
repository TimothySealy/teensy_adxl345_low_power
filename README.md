# Teensy LC and ADXL345
This configuration shows a simple (low power) "wake on shake" implementation using a Teensy (LC) and ADXL345 accelerometer.

## Bill of materials
* Teensy LC
* GY-291 ADXL345 3-axis accelerometer
* 2x 4K7 Ohm resistors
* Hookup wires

## Fritzing
The ADXL345 is configured to communicate with the Teensy over I2C.

## Sketch
In this repository you will find a sketch which will configure the ADXL345 to trigger an interrupt on activity. The ADXL is set in low power mode. The Teensy  is put in Hibernate mode. When an interrupt is triggered upon activity the builtin LED on the Teensy will blink. After that the Teensy is put in Hibernate mode and the cycle repeats.

The sketch includes the following libraries:
* [Snooze](https://github.com/duff2013/Snooze) - Teensy low power library
* [Sparkfun ADXL345](https://github.com/sparkfun/SparkFun_ADXL345_Arduino_Library) library
