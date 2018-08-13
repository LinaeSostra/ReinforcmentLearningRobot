#include "ValueFunctionApproximator.h"
#include "Vector.h"

float weights[NUM_FEATURES] = {0};

void extractFeatures(const State &state, const Action action, float phi[]) {
  // 1 - Counterclockwise
  //-1 - Clockwise
  int8_t leftMotorDirection = 0;
  int8_t rightMotorDirection = 0;
  int8_t angleDirection = 0;

  switch (action) {
    case Stay:
      break;
    case Forward:
      leftMotorDirection = -1;
      rightMotorDirection = -1;
      break;
    case Backwards:
      leftMotorDirection = 1;
      rightMotorDirection = 1;
      break;
    case Right:
      leftMotorDirection = -1;
      rightMotorDirection = 1;
      angleDirection = -1;
      break;
    case Left:
      leftMotorDirection = 1;
      rightMotorDirection = -1;
      angleDirection = 1;
      break;
  }
 squareBinBinaryAugment(float(state.xPosition), float(state.yPosition), state.angle, 20, phi, 1600);
  phi[1600] = float(leftMotorDirection);
  phi[1601] = float(rightMotorDirection);
  phi[1602] = float(angleDirection && (state.angle == North));
  phi[1603] = float(angleDirection && (state.angle == West));
  phi[1604] = float(angleDirection && (state.angle == South));
  phi[1605] = float(angleDirection && (state.angle == East));
}

float value(const State &state, const Action action) {
  float phi[NUM_FEATURES];
  extractFeatures(state, action, phi);
  return dot(weights, phi, NUM_FEATURES);
}

// Note: may need to add bins back if make state space larger
void squareBin(const float xPosition, const float yPosition, const uint8_t sideLength, float vector[], size_t length) {
  uint16_t binIndex = sideLength * yPosition + xPosition;
  bool doesIndexMatch = false;
  
  for (uint16_t i = 0; i < length; i++) {
    doesIndexMatch = i == binIndex;
    vector[i] = (doesIndexMatch) ? 1.0: 0.0;
  }
}

void squareBinBinaryAugment(const float xPosition, const float yPosition, const Angle angle, const uint8_t sideLength, float vector[], size_t length) {
  uint16_t binIndex = sideLength * yPosition + xPosition;
  bool doesIndexMatch = false;

  switch (angle) {
  case West:
    binIndex += sideLength * sideLength;
    break;
  case East:
    binIndex += 2 * sideLength * sideLength;
    break;
  case South:
    binIndex += 3 * sideLength * sideLength;
    break;
  }
  
  for(uint16_t i = 0; i < length; i++) {
    doesIndexMatch = i == binIndex;
    vector[i] = (doesIndexMatch) ? 1.0 : 0.0;
  }
}
