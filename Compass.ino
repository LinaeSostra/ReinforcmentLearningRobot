/* Compass */

void gatherAccelometerValues() {
  // Get a new sensor event
  sensors_event_t event;
  accelometer.getEvent(&event);

#ifdef DEBUG
   // Display the results (acceleration is measured in m/s^2)
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
#endif

  // Delay for next sample
  delay(500);
}

