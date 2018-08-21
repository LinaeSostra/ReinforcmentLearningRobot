//TODO(Rebecca): Fix these to be proper calls.
bool batteryLow = false;

bool isCompassNorth() {
  State currentState = getCurrentState();
  return currentState.angle == 0;
}

// Termination occurs  when robot gets to location (5,5) and is pointing North
bool stateIsTerminal(const State &state) {
  bool atEndPosition = (state.xPosition == END_POSITION && state.yPosition == END_POSITION && state.angle == North);
  return atEndPosition;
  //TODO: This will be more complex if Benny actually works...
  //return getLatch();
}

int calculateReward(const State &state, const Action action, const State &statePrime) {
  if(stateIsTerminal(statePrime)) {
    return 50;
  }
  
  bool isXOutOfBounds = statePrime.xPosition > MAX_POSITION || statePrime.xPosition < MIN_POSITION;
  bool isYOutOfBounds = statePrime.yPosition > MAX_POSITION || statePrime.yPosition < MIN_POSITION;
  if(isXOutOfBounds || isYOutOfBounds) {
    return -100;
  }
  
  if(batteryLow) {
    return -50;
  }

  //TODO: Likely don't need this, but to encourage the right kind of action for now.
  if(isCompassNorth()) {
    return -1;
  }

  return -2;
}