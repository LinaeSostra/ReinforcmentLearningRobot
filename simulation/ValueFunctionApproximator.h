#ifndef VALUEFUNCTIONAPPROXIMATOR_H
#define VALUEFUNCTIONAPPROXIMATOR_H
#include "Learning.h"

void extractFeatures(const State &state, const Action action, double phi[]);

double value(const State &state, Action action);

void squareBin(const State &state, const unsigned int sideLength, double vector[], unsigned int length);

void squareBinBinaryAugment(const State &state, const unsigned int sideLength, double vector[], unsigned int length);
#endif