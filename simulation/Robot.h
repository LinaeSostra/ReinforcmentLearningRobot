#ifndef ROBOT_H
#define ROBOT_H
#include "Learning.h"
#include <iostream>
#include <assert.h>

using namespace std;

State getCurrentState(); // Returns the current state of the robot
State getStep(const State &state, Action action); //Calculates new state if action applied to given state
void resetPosition(); // Reset robot to starting location
void resetToRandomPosition(); // Reset robot to random starting location
void logState(); // Save the robot's state
void apply(Action action); // Adjust the robot's states
#endif
