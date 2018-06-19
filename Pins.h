#ifndef PINS_H
#define PINS_H

// 16 D0  - Non-interruptable
const int pinBatteryRead = A0;      // A0
const int pinMotorA1 = 0;           // D3
const int pinMotorA2 = 2;           // D4
const int pinMotorB1 = 14;          // D5
const int pinMotorB2 = 12;          // D6
const int pinPushSensor = 13;           // D7
// 15 D8
const int pinSpeedMotorA = 1;       // Tx
const int pinSpeedMotorB = 3;       // Rx
// Note: There is something weird about this output 9 on this particular microcontroller.
// 9 SD2
const int pinLED = 10; // SD3

#endif
