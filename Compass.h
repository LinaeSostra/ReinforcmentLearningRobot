#ifndef COMPASS_H
#define COMPASS_H

void compassSetup();
void gatherAccelometerReadings();
void gatherMagnetometerReadings();
void testMagneticValues();
void getAngleDirection();
void calibrateMagneticReadings();
#endif
