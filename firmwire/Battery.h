#ifndef BATTERY_H
#define BATTERY_H

#define BATTERY_VOLTAGE_MAX 8.4 // 4.2 x 2
#define BATTERY_VOLTAGE_MIN 6.4  // 3.2 x 2

#define R1 47 // 47k
#define R2 100 // 100k

#define LOW_BATTERY_PERCENTAGE 20.0 // %

void batterySetup();

void calculateVoltage();
void checkBattery();
void turnLEDs();
bool isBatteryLow();

float getBatteryLevel();
float getBatteryPercentage();

#endif
