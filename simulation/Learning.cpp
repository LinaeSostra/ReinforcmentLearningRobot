#include "Learning.h"
#include "Task.h"
#include "ValueFunctionApproximator.h"

// Percentage (between 0 - 100)
int epsilon = DEFAULT_EPSILON;
double alpha = DEFAULT_ALPHA;
double learningRate = 1.0; // Note: Gamma, but Arduino "gamma" keyword reserved.

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

int getRandomNumber(const int modulo) {
  return (rand() % modulo);
}

Action chooseRandomAction() { 
  return (Action) getRandomNumber(NUM_ACTIONS);
}

Action chooseGreedyAction(const State &state) {
  double maxValue = -100000.0;
  Action bestActions[NUM_ACTIONS] = {};
  int numOfBestActions = -1;
  for(int i = 0; i < NUM_ACTIONS; i++) {
    double candidateValue = value(state, (Action)i);
   // cout << "(Action, Value): ("<< i << ", " << candidateValue << ")\n";
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
  Action bestAction = bestActions[getRandomNumber(numOfBestActions)];
  //cout << "Best Action Selected: " << bestAction << "\n";
  return bestAction;
}

Action chooseAction(const State &state) {
  // If randomly below epilson, choose random action
  bool shouldExplore = getRandomNumber(PERCENTAGE) < epsilon;
  return shouldExplore ? chooseRandomAction() : chooseGreedyAction(state);
}

// Episodic Semi-gradient Sarsa for Control.
// Refer to Reinforcement Learning: An Introduction 2nd ed. (Sutton and Barto) page 230.
void updateSarsa(State &state, Action action, State &statePrime) {
  Action actionPrime = chooseAction(statePrime);
  //cout << "Action Selection: " << actionPrime << "\n";
  double reward = calculateReward(state, action, statePrime);
  //cout << "Expected Reward for state transition: " << reward << "\n";

  // Find expected value of next (state, action)
  double tempWeights[NUM_FEATURES];
  extractFeatures(statePrime, actionPrime, tempWeights);
  double valuePrime = calculateDot(weights, tempWeights, NUM_FEATURES);
  //cout << "Expected Value for state transition: " << valuePrime << "\n";

  // Find change in weight value of current (state, action), and update theta
  extractFeatures(state, action, tempWeights);
  double weightError = alpha * (reward + learningRate * valuePrime - calculateDot(weights, tempWeights, NUM_FEATURES));
  multiply(weightError, tempWeights, NUM_FEATURES);
  add(weights, tempWeights, NUM_FEATURES);

  //  Update global variables
  nextAction = actionPrime;
  lastReward = reward;
}

// Episode Semi-gradient Q-Learning
void updateQLearning(State &state, Action action, State &statePrime) {
  double reward = calculateReward(state, action, statePrime);

  double tempWeights[NUM_FEATURES];
  extractFeatures(statePrime, chooseGreedyAction(statePrime), tempWeights);
  double valuePrime = calculateDot(weights, tempWeights, NUM_FEATURES);

  extractFeatures(state, action, tempWeights);
  double weightError = alpha * (reward  + learningRate * valuePrime - calculateDot(weights, tempWeights, NUM_FEATURES));
  multiply(weightError, tempWeights, NUM_FEATURES);
  add(weights, tempWeights, NUM_FEATURES);

  nextAction = chooseAction(statePrime);
  lastReward = reward;
}