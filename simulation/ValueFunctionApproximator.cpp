#include "ValueFunctionApproximator.h"

double weights[NUM_FEATURES] = {0};

void resetWeights() {
  for(unsigned i = 0; i < NUM_FEATURES; i++) {
    weights[i] = 0.0;
  }
}

void squareBinBinaryAugment(const State &state, const int sideLength, double vector[], unsigned int length) {
  double xPosition = (double) state.position.x;
  double yPosition = (double) state.position.y;
  unsigned int binIndex = (int) (sideLength * yPosition + xPosition);
  bool doesIndexMatch = false;

  switch (state.angle) {
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
  
  for(unsigned int i = 0; i < length; i++) {
    doesIndexMatch = i == binIndex;
    vector[i] = (doesIndexMatch) ? 1.0 : 0.0;
  }
}

void extractFeatures(const State &state, const Action action, double phi[]) {
  State newState = getStep(state, action);
  const int sideLength = MAX_POSITION - MIN_POSITION + 1;
  squareBinBinaryAugment(newState, sideLength, phi, NUM_FEATURES);
}

double value(const State &state, const Action action) {
  double phi[NUM_FEATURES];
  extractFeatures(state, action, phi);
  double value = 0.0;
  bool isPhiEmpty = true;
  for(unsigned int i = 0; i < NUM_FEATURES; i++) {
    if(phi[i] != 0.0) {
      isPhiEmpty = false;
    }
    value += weights[i] * phi[i];
  }
  return isPhiEmpty ? -100 : value;
}

// Note: may need to add bins back if make state space larger
void squareBin(const State &state, const unsigned int sideLength, double vector[], unsigned int length) {
  double xPosition = (double) state.position.x;
  double yPosition = (double) state.position.y;
  unsigned int binIndex = (int) (sideLength * yPosition + xPosition);

  bool doesIndexMatch = false;
  for (int i = 0; i < length; i++) {
    doesIndexMatch = i == binIndex;
    vector[i] = (doesIndexMatch) ? 1.0: 0.0;
  }
}