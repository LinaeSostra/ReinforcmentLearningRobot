/* Power */

// Returns how much battery juice is left
int getVoltage() {
  // Voltage reading is divided, two cells is 7.4v in average
  // Vout=Vin*(R1/(R1+R2))

  float batteryVoltage = analogRead(pinBatteryRead) * (3.3 / 1023) * (R1 + R2) / R1; // Recommended range: 3.2v-4.2v as 0%-100%

#ifdef DEBUG
  Serial.print("Battery voltage (v): ");
  Serial.println(batteryVoltage);
#endif

  float batteryPercentage = (batteryVoltage - batteryVoltageMin) / (batteryVoltageMax - batteryVoltageMin) * 100; // Percentage calculation
  
#ifdef DEBUG
  Serial.print("Battery Percentage (%): ");
  Serial.println(batteryPercentage);
#endif

  batteryLevel =  batteryVoltage; // Calibrate the reading with an offset if needed

  return batteryLevel;
}
