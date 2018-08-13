#include "ValueFunctionApproximator.h"
#include "Task.h"
#include "Vector.h"

//  Private Variables to Learning.
extern float lastReward;
extern Action nextAction;
extern float theta[];

// Percentage (between 0 - 100)
uint8_t epsilon = DEFAULT_EPSILON;
float alpha = DEFAULT_ALPHA;
float learningRate = 0.99; // Note: Gamma, but Arduino "gamma" keyword reserved.

void logWeights() {
  logVector(theta, NUM_FEATURES);
}

// Episodic Semi-gradient Sarsa for Control.
// Refer to Reinforcement Learning: An Introduction 2nd ed. (Sutton and Barto) page 230.
void update(State &state, Action action, State &statePrime) { 
  Action actionPrime = chooseAction(statePrime);
  float reward = calculateReward(state, action, statePrime);

  // Find expected value of next (state, action)
  float weights[NUM_FEATURES];
  extractFeatures(statePrime, actionPrime, weights);
  float valuePrime = dot(theta, weights, NUM_FEATURES);

  // Find change in weight value of current (state, action), and update theta
  extractFeatures(state, action, weights);
  float weightError = alpha * (reward + learningRate * valuePrime - dot(theta, weights, NUM_FEATURES));
  multiply(weightError, weights, NUM_FEATURES);
  add(theta, weights, NUM_FEATURES);
}

Action chooseRandomAction() { 
  return (Action)random(0, NUM_ACTIONS + 1);
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
      bestActions[0] = (Action)i;
      numOfBestActions = 1;
    // I really doubt there are multiply actions that are of equal value, but 
    } else if (candidateValue == maxValue) {
      bestActions[numOfBestActions] = (Action)i;
      numOfBestActions += 1;
    }
  }
  return bestActions[random(numOfBestActions)];
}