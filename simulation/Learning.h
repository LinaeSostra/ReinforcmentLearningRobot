#ifndef LEARNING_H
#define LEARNING_H

#include <cstdlib>

#define PERCENTAGE 100
#define DEFAULT_ALPHA 0.2
#define DEFAULT_EPSILON 10
#define NUM_ACTIONS  4

#define MIN_POSITION 0//-10
#define MAX_POSITION 4//9

#define START_POSITION 0
#define END_POSITION 4//5

typedef enum Angle {
  North = 90,
  West = 180,
  South = 270,
  East = 0
} Angle;

typedef struct State {
  int xPosition;
  int yPosition;
  Angle angle;
} State;

// The robot has 4 options: Move Forward, Move Backwards, Turn Left, Turn Right
typedef enum Action {
  Forward,
  Backwards,
  Right,
  Left
} Action;

// 20 [-10:9] in x and y direction + 4 angles
// 20*20*4 = 3200 features
//const unsigned int NUM_FEATURES = 400;

// 5 [-2:2] in x and y direction + 4 angles
// 5*5*4 = 100 features
const unsigned int NUM_FEATURES = 100;

//  Private Variables to Learning.
extern double lastReward;
extern Action nextAction;
extern double weights[NUM_FEATURES];

Action chooseRandomAction();
Action chooseAction(const State &state);
void update(const State &state, const Action action, const State &statePrime);

#endif
