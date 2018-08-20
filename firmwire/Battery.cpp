/* Battery */
#include <Arduino.h>
#include "Pins.h"
#include "Battery.h"

#define DEBUG // comment this line to disable debug (Serial Prints)

float batteryLevel = 0;

void batterySetup() {
  pinMode(pinBatteryRead, INPUT);
  pinMode(pinLED, OUTPUT);
}

// Calculates how much battery juice is left
void calculateVoltage() {
  // Voltage reading is divided, two cells is 7.4v in average
  // Vout=Vin*(R1/(R1+R2))

  float batteryVoltage = analogRead(pinBatteryRead) * (3.3 / 1023) * (R1 + R2) / R1; // Recommended range: 3.2v-4.2v as 0%-100%
#ifdef DEBUG
  Serial.print("Battery voltage (v): ");
  Serial.println(batteryVoltage);
#endif
  batteryLevel =  batteryVoltage; // Calibrate the reading with an offset if needed
}

bool isBatteryLow() {
  float batteryPercentage = getBatteryPercentage();
  bool withinBatteryRange = batteryPercentage > 0.0;
  bool isBatteryLow = batteryPercentage < LOW_BATTERY_PERCENTAGE;
  return withinBatteryRange && isBatteryLow;
}

// Turn on the LED when battery is low
void turnLEDs() {
  bool batteryLow = isBatteryLow();

  if(batteryLow) {
    digitalWrite(pinLED, HIGH);
  } else {
    digitalWrite(pinLED, LOW);
  }
}

void checkBattery() {
  calculateVoltage();
  turnLEDs();
}

/* Getters */
float getBatteryLevel() {
  return batteryLevel;
}

/* Helper Functions */
float getBatteryPercentage() {
  float batteryPercentage = (batteryLevel - BATTERY_VOLTAGE_MIN) / (BATTERY_VOLTAGE_MAX - BATTERY_VOLTAGE_MIN) * 100; // Percentage calculation
#ifdef DEBUG
  Serial.print("Battery Percentage: ");
  Serial.println(batteryPercentage);
#endif
  return batteryPercentage;
}
