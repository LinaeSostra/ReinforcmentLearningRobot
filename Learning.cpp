#include "Learning.h"
#include "ValueFunctionApproximator.h"
#include "Task.h"
#include "Vector.h"

//  Private Variables to Learning.
float lastReward;
Action nextAction;
float theta[];

// Percentage (between 0 - 100)
uint8_t epsilon = DEFAULT_EPSILON;
float aplha = DEFAULT_ALPHA;
float gamma = 0.99;

void update(State &state, Action action, State &statePrime) { }

Action chooseRandomAction() { 
  return (Action)random(0, NUM_ACTIONS+1);
}

Action chooseAction(const State &state) {
  // If randomly below epilson, choose random action
  if(random(101) < epsilon) {
    return chooseRandomAction();
  }

  // Else, find the best greedy action
  float maxValue = -100000.0;
  Action bestActions[NUM_ACTIONS] = {};
  uint8_t numOfBestActions = -1;
  for(uint8_t i = 0; i < NUM_ACTIONS; i++) {
    float candidateValue = value(state, (Action)i);
    if (candidateValue > maxValue) {
      maxValue = candidateValue;
      bestActions[0] - (Action)i;
      numOfBestActions = 1;
    // I really doubt there are multiply actions that are of equal value, but 
    } else if (candidateValue == maxValue) {
      bestActions[numOfBestActions] = (Action)i;
      numBestActions += 1;
    }
  }
  return bestActions[random(numOfBestActions)];
}

