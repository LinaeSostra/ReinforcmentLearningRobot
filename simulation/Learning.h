#ifndef LEARNING_H
#define LEARNING_H

#include <cstdlib>

#define PERCENTAGE 100
#define DEFAULT_ALPHA 0.2
#define DEFAULT_EPSILON 10
#define NUM_ACTIONS  5

#define MIN_POSITION -10
#define MAX_POSITION 9

#define START_POSITION 0
#define END_POSITION 5

typedef enum Angle {
  North = 0,
  West = 90,
  South = 180,
  East = 270
} Angle;

typedef struct State {
  int xPosition;
  int yPosition;
  Angle angle;
} State;

// The robot has 5 options: Move Forward, Move Backwards, Turn Left, Turn Right, Stay
typedef enum Action {
  Stay,
  Forward,
  Backwards,
  Right,
  Left
} Action;

// 20 [-10:9] in x and y direction + 4 angles
// 20*20*4 = 3200 features
const unsigned int NUM_FEATURES = 1606;

//  Private Variables to Learning.
extern double lastReward;
extern Action nextAction;
extern double weights[NUM_FEATURES];

Action chooseRandomAction();
Action chooseAction(const State &state);
void update(const State &state, const Action action, const State &statePrime);

#endif
