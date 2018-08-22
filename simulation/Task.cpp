//TODO(Rebecca): Fix these to be proper calls.
bool batteryLow = false;

bool isCompassNorth(const State &state) {
  return state.angle == North;
}

bool didStateChange(const State &state, const State &statePrime) {
  bool xPositionChange = state.xPosition != statePrime.xPosition;
  bool yPositionChange = state.yPosition != statePrime.yPosition;
  bool angleChange = state.angle != statePrime.angle;
  return xPositionChange || yPositionChange || angleChange; 
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
  
  //bool isXOutOfBounds = statePrime.xPosition > MAX_POSITION || statePrime.xPosition < MIN_POSITION;
  //bool isYOutOfBounds = statePrime.yPosition > MAX_POSITION || statePrime.yPosition < MIN_POSITION;
  
  bool hitAWall = (action == Forward || action == Backwards) && !didStateChange(state, statePrime);
  if(hitAWall) {
    //cout << "Hit a Wall!!\n";
    return -100;
  }
  
  if(batteryLow) {
    return -50;
  }

  //TODO: Likely don't need this, but to encourage the right kind of action for now.
  if(isCompassNorth(statePrime)) {
    return -1;
  }

  return -2;
}