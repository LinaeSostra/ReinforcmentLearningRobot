/* Power */

////////////////////////////////
/* Global Constants */
////////////////////////////////
const float batteryVoltageMax = 8.4; // 4.2 x 2
const float batteryVoltageMin = 6.4; // 3.2 x 2
const int R1 = 47; // 47k
const int R2 = 100; // 100k

const float lowBatteryThreshold = 20.0;

////////////////////////////////
/* Global Variables */
////////////////////////////////
float batteryLevel = 0;

////////////////////////////////
/* Functions */
////////////////////////////////
/* Setters */
void checkBattery() {
  calculateVoltage();
  turnLEDs();
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

// Turn on the LED when battery is low
void turnLEDs() {
  float batteryPercentage = getBatteryPercentage();
  bool isBatteryLow = batteryPercentage < lowBatteryThreshold && batteryPercentage > 0.0;

  if(isBatteryLow) {
    digitalWrite(pinLED, HIGH);
  } else {
    digitalWrite(pinLED, LOW);
  }
}

/* Getters */
float getBatteryLevel() {
  return batteryLevel;
}

/* Helper Functions */
float getBatteryPercentage() {
  float batteryPercentage = (batteryLevel - batteryVoltageMin) / (batteryVoltageMax - batteryVoltageMin) * 100; // Percentage calculation
#ifdef DEBUG
  Serial.print("Battery Percentage: ");
  Serial.println(batteryPercentage);
#endif
  return batteryPercentage;
}
