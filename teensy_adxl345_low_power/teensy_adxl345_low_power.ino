#include <Snooze.h>
#include <SparkFun_ADXL345.h>

#define SERIAL_OUTPUT 0
#define ADXL_INT_PIN 22

// Load drivers
SnoozeDigital digital;
Snoozelc5vBuffer lc5vBuffer;

// install drivers to a SnoozeBlock
SnoozeBlock config_teensyLC(digital, lc5vBuffer);

// Create an ADXL345 instance.
ADXL345 adxl = ADXL345();

void setup() {
  
#if SERIAL_OUTPUT == 1 
  Serial.begin(38400);
  Serial.println("Start...");
#endif

  // Power on the ADXL345
  adxl.powerOn();
             
  // Give the range settings, accepted values are 2g, 4g, 8g or 16g
  // Higher Values = Wider Measurement Range
  // Lower Values = Greater Sensitivity
  adxl.setRangeSetting(8);  

  // Set to activate movement detection on all axes (1 == ON, 0 == OFF)
  adxl.setActivityXYZ(1, 1, 1);
  adxl.setActivityThreshold(50);
  
  // Setting all interupts to take place on INT1 pin.
  adxl.setImportantInterruptMapping(0, 0, 0, 1, 0);     
  
  // Turn on Interrupts for each mode (1 == ON, 0 == OFF).
  adxl.ActivityINT(1);
  adxl.InactivityINT(0);
  adxl.FreeFallINT(0);
  adxl.doubleTapINT(0);
  adxl.singleTapINT(0);
  
  // Turn on power saving features.
  adxl.setRate(12.5);
  adxl.setLowPower(1);

  // Clear interrupt registers.
  adxl.getInterruptSource();

#if SERIAL_OUTPUT == 1 
  // Debug info
  adxl.printAllRegister();
#endif

  // Configure pins.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ADXL_INT_PIN, INPUT);
  
  // Set adxl interrupt pin to wake up teensy.
  digital.pinMode(ADXL_INT_PIN, INPUT, RISING);

  // Don't immediately put the Teensy asleep.
  delay(100);
}

void loop() {
  // Put Teensy in low power mode (hibernate).
  int who = Snooze.hibernate( config_teensyLC );

  // Wake up. Read interrupt register to check if activity was triggered.
  byte interrupts = adxl.getInterruptSource();
  if(adxl.triggered(interrupts, ADXL345_ACTIVITY)) {

    // Blink (visual feedback)
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    
#if SERIAL_OUTPUT == 1
    Serial.println("Active");
#endif
  }

}
