#ifndef VECTOR_H
#define VECTOR_H

#include <Arduino.h>

void logVector(const float vector[], size_t length);

//TODO: Unsure if need this one just yet.
float dot(const uint8_t anArray[], const uint8_t secondArray[], size_t length);

float dot(const float anArray[], const float secondArray[], size_t length);

//Note, this anArray will be added to, thus not specified as const
void add(float anArray[], const float secondArray[], size_t length);

void multiply(const float scalar, float anArray[], size_t length);
#endif
