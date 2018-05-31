/* Power */

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

// Turn on the LED when Battery is low
void turnLEDs() {
  float batteryPercentage = getBatteryPercentage();
  bool isBatteryLow = batteryPercentage < 40.0 && batteryPercentage > 0.0;

  if(isBatteryLow) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

float getBatteryPercentage() {
  float batteryPercentage = (batteryLevel - batteryVoltageMin) / (batteryVoltageMax - batteryVoltageMin) * 100; // Percentage calculation
#ifdef DEBUG
  Serial.print("Battery Percentage: ");
  Serial.println(batteryPercentage);
#endif
  return batteryPercentage;
}

void checkBattery() {
  calculateVoltage();
  turnLEDs();
}
