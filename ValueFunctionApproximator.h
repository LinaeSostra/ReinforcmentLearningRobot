#ifndef VALUEFUNCTIONAPPROXIMATOR_H
#define VALUEFUNCTIONAPPROXIMATOR_H

#include <Arduino.h>
#include "Learning.h"

// 20 [-10:9] in x and y direction + 8 angles
// 20*20*8 = 3200 features
const int NUM_FEATURES = 3200;

void extractFeatures(const State &state, const Action action, float phi[]);

float value(const State &state, Action action);

void squareBin(const float xPosition, const float yPosition, const float bin, const uint8_t sideLength, float vector[], size_t length);

void squareBinBinaryAugment(const float xPosition, const float yPosition, const bool binaryValue, const float bin, const uint8_t sideLength, float vector[], size_t length); 
#endif
