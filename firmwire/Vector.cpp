#include "Vector.h"
#include "Strings.h"

// Logging for debugging purposes
void logVector(const float anArray[], size_t length) {
  Serial.print("[");
  for( uint8_t i = 0; i < length; i++) {
    float value = anArray[i];
    Serial.print(" ");
    Serial.print(value);
  }
  Serial.println("]");
}

float dot(const uint8_t anArray[], const uint8_t secondArray[], size_t length) {
  float result = 0.0;
  for( uint8_t i = 0; i < length; i++) {
    result += float(anArray[i]) * float(secondArray[i]);
  }
  return result;
}

float dot(const float anArray[], const float secondArray[], size_t length) {
  float result = 0.0;
  for( uint8_t i = 0; i < length; i++) {
    result += anArray[i] * secondArray[i];
  }
  return result;
}

void add(float anArray[], const float secondArray[], size_t length) {
  for(uint8_t i = 0; i < length; i++) {
    anArray[i] += secondArray[i];
  }
}

void multiply(const float scalar, float anArray[], size_t length) {
  for(uint8_t i = 0; i < length; i++) {
    anArray[i] *= scalar;
  }
}
