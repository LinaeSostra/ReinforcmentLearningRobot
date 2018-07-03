/* Compass */
const double xMagOffset = 340.00;
const double yMagOffset = -80.00;
const double zMagOffset = -156.00;
void gatherAccelometerValues() {
  // Get a new sensor event
  sensors_event_t event;
  accelometer.getEvent(&event);

#ifdef DEBUG
   // Display the results (acceleration is measured in m/s^2)
  Serial.print("\nX: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");

#endif

  // Delay for next sample
  delay(500);
}

void gatherMagneticValues() {
  // Get a new sensor event;
  sensors_event_t event;
  mag.getEvent(&event);

#ifdef DEBUG
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  Serial.print("\nX: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
#endif

  // Delay for next sample
  delay(500);
  
}

