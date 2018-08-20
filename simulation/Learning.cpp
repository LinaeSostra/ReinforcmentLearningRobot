#include "Learning.h"
#include "Task.h"
#include "ValueFunctionApproximator.h"

// Percentage (between 0 - 100)
int epsilon = DEFAULT_EPSILON;
double alpha = DEFAULT_ALPHA;
double learningRate = 0.99; // Note: Gamma, but Arduino "gamma" keyword reserved.

void logWeights() {
  cout << "[";
  for( unsigned int i = 0; i < NUM_FEATURES; i++) {
    double value = weights[i];
    cout << " " << value;
  }
  cout << "]\n";
}

double calculateDot(double array[], double array2[], unsigned int length) {
  double result = 0.0;
  for (unsigned int i = 0; i < length; i++) {
    result += array[i]*array2[i];
  }
  return result;
}

void multiply(const double scalar, double array[], unsigned int length) {
  for (unsigned int i = 0; i < length; i++) {
    array[i] *= scalar;
  }
}

void add(double array[], double array2[], unsigned int length) {
  for (unsigned int i = 0; i < length; i++) {
    array[i] += array2[i];
  }
}

// Episodic Semi-gradient Sarsa for Control.
// Refer to Reinforcement Learning: An Introduction 2nd ed. (Sutton and Barto) page 230.
void update(State &state, Action action, State &statePrime) { 
  Action actionPrime = chooseAction(statePrime);
  double reward = calculateReward(state, action, statePrime);

  // Find expected value of next (state, action)
  double tempWeights[NUM_FEATURES];
  extractFeatures(statePrime, actionPrime, tempWeights);
  double valuePrime = calculateDot(weights, tempWeights, NUM_FEATURES);

  // Find change in weight value of current (state, action), and update theta
  extractFeatures(state, action, tempWeights);
  double weightError = alpha * (reward + learningRate * valuePrime - calculateDot(weights, tempWeights, NUM_FEATURES));
  multiply(weightError, tempWeights, NUM_FEATURES);
  add(weights, tempWeights, NUM_FEATURES);
}

int getRandomNumber(const int modulo) {
  return ((rand() % modulo) + 1);
}

Action chooseRandomAction() { 
  return (Action) getRandomNumber(NUM_ACTIONS);
}

Action chooseAction(const State &state) {
  // If randomly below epilson, choose random action
  if(getRandomNumber(PERCENTAGE) < epsilon) {
    return chooseRandomAction();
  }

  // Else, find the best greedy action
  double maxValue = -100000.0;
  Action bestActions[NUM_ACTIONS] = {};
  int numOfBestActions = -1;
  for(int i = 0; i < NUM_ACTIONS; i++) {
    double candidateValue = value(state, (Action)i);
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
  return bestActions[getRandomNumber(numOfBestActions) - 1];
}