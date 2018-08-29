#ifndef MAIN_H
#define MAIN_H

#include "Robot.cpp"
#include "Learning.cpp"
#include "ValueFunctionApproximator.cpp"
#include "Task.cpp"
#include "Strings.h"
#include "UI.cpp"
#include <iostream>
#include <sys/types.h>
#include <ctime>
#include <string>

#define NUM_OF_RUNS 1
#define EVALUATION_SWITCH_POINT 500//1000//50
#define EVALUATION_MAX_STEPS 200//200

// Variables
extern State currentState;
extern State previousState;
#endif