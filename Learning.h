#ifndef LEARNING_H
#define LEARNING_H

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

#endif
