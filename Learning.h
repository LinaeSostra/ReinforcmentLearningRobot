#ifndef LEARNING_H
#define LEARNING_H

typedef struct State {
  int xPosition;
  int yPosition;
  unsigned int angle;
} State;

// The robot has 5 options: Move Forward, Move Backwards, Turn Left, Turn Right, Stay
typedef enum Action {
  Stay,
  Forward,
  Backward,
  Left,
  Right
} Action;
#endif
