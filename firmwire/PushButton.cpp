#include <Arduino.h>
#include "Pins.h"
#include "PushButton.h"

bool isSensorPushed = false;

void latchSetup() {
  pinMode(pinPushSensor, INPUT_PULLUP);

  // Attach Interrupts
  attachInterrupt(digitalPinToInterrupt(pinPushSensor), latchTriggered, CHANGE);
}

// Interrupt Fcn: When the push sensor changes state, update isSensorPushed boolean
void latchTriggered() {
#ifdef DEBUG
  Serial.print("Is Sensor Pushed: "); Serial.println(getSensorPushed());
#endif
  isSensorPushed = !isSensorPushed;
}

bool getLatch() {
  return isSensorPushed;
}

