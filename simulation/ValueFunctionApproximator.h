#ifndef VALUEFUNCTIONAPPROXIMATOR_H
#define VALUEFUNCTIONAPPROXIMATOR_H
#include "Learning.h"

// 20 [-10:9] in x and y direction + 4 angles
// 20*20*4 = 3200 features
//const int NUM_FEATURES = 1606;

void extractFeatures(const State &state, const Action action, double phi[]);

double value(const State &state, Action action);

void squareBin(const double xPosition, const double yPosition, const unsigned int sideLength, double vector[], unsigned int length);

void squareBinBinaryAugment(const double xPosition, const double yPosition, const bool binaryValue, const unsigned int sideLength, double vector[], unsigned int length); 
#endif