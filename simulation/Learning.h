#ifndef LEARNING_H
#define LEARNING_H

#include <cstdlib>

#define PERCENTAGE 101
#define DEFAULT_ALPHA 0.2
#define DEFAULT_EPSILON 10
#define NUM_ACTIONS  4

#define MIN_POSITION 0//-10
#define MAX_POSITION 9//9

#define START_POSITION 0
#define END_POSITION 4//5

typedef enum Angle {
  North = 90,
  West = 180,
  South = 270,
  East = 0
} Angle;

struct Position {
  int x;
  int y;
};

bool operator==(const Position &position, const Position &position2) {
  return position.x == position2.x && position.y == position2.y;
}

void operator+=(Position &position, const Position &position2) {
  position.x += position2.x;
  position.y += position2.y;
}

typedef struct State {
  Position position;
  Angle angle;
} State;

bool operator==(const State &state, const State &state2) {
  return state.position == state2.position && state.angle == state2.angle;
}

// The robot has 4 options: Move Up, Move Down, Move Left, Move Right
typedef enum Action {
  Up,
  Down,
  Left,
  Right
} Action;

// 20 [-10:9] in x and y direction + 4 angles
// 20*20*4 = 1600 features
//const unsigned  int NUM_FEATURES = 1600;

//  10 [0:9] in x and y direction + 4 angles
// 10*10*4 = 400 features
const unsigned int NUM_FEATURES = 400;

// 5 [0:4] in x and y direction + 4 angles
// 5*5*4 = 100 features
//const unsigned int NUM_FEATURES = 100;

const Position START_LOCATION = {START_POSITION, START_POSITION};
const Position END_LOCATION = {END_POSITION, END_POSITION};

//  Private Variables to Learning.
extern double lastReward;
extern Action nextAction;
extern double weights[NUM_FEATURES];

Action chooseRandomAction();
Action chooseAction(const State &state);
void update(const State &state, const Action action, const State &statePrime);

#endif
