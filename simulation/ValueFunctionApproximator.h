#ifndef VALUEFUNCTIONAPPROXIMATOR_H
#define VALUEFUNCTIONAPPROXIMATOR_H
#include "Learning.h"

void extractFeatures(const State &state, const Action action, double phi[]);

double value(const State &state, Action action);

void squareBin(const double xPosition, const double yPosition, const unsigned int sideLength, double vector[], unsigned int length);

void squareBinBinaryAugment(const double xPosition, const double yPosition, const bool binaryValue, const unsigned int sideLength, double vector[], unsigned int length); 
#endif