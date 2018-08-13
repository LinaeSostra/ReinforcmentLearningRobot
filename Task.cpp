#include <Arduino.h>
#include "Learning.h"
#include "PushButton.h"

//TODO(Rebecca): Fix these to be proper calls.
bool batteryLow = false;
bool isCompassNorth = false;

// Termination occurs  when robot gets to location (5,5) and is pointing North
bool stateIsTerminal(const State &state) { 
  return (state.xPosition == 5 && state.yPosition == 5 && state.angle == North);
  //TODO: This will be more complex if Benny actually works...
  //return getLatch();
}

int8_t calculateReward(const State &state, const Action action, const State &statePrime) {
  if(stateIsTerminal(statePrime)) {
    return 50;
  }
  
  bool isXOutOfBounds = abs(statePrime.xPosition) >= 10;
  bool isYOutOfBounds = abs(statePrime.yPosition) >= 10;
  if(isXOutOfBounds || isYOutOfBounds) {
    return -100;
  }
  
  if(batteryLow) {
    return -50;
  }

  //TODO: Likely don't need this, but to encourage the right kind of action for now.
  if(isCompassNorth) {
    return -1;
  }

  return -2;
}

