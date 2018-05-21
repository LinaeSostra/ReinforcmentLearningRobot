/* Motion */

void testMotors() {
  moveCW(); // Rotate in Clockwise
  delay(5000); // Wait 5 seconds
  moveCCW(); // Rotate in Counter-Clockwise
  delay(5000); // Wait 5 seconds
  moveForward(); // Move forward
  delay(5000); // Wait 5 seconds
  moveBackward(); // Move backward
  delay(5000); // Wait 5 seconds
}

void moveCW() {
  digitalWrite(pinMotorA1, LOW);
  digitalWrite(pinMotorA2, HIGH);
  digitalWrite(pinMotorB1, LOW);
  digitalWrite(pinMotorB2, HIGH);
}

void moveCCW() {
  digitalWrite(pinMotorA1, HIGH);
  digitalWrite(pinMotorA2, LOW);
  digitalWrite(pinMotorB1, HIGH);
  digitalWrite(pinMotorB2, LOW);
}

void moveForward() {
  digitalWrite(pinMotorA1, HIGH);
  digitalWrite(pinMotorA2, LOW);
  digitalWrite(pinMotorB1, LOW);
  digitalWrite(pinMotorB2, HIGH);
}

void moveBackward() {
  digitalWrite(pinMotorA1, LOW);
  digitalWrite(pinMotorA2, HIGH);
  digitalWrite(pinMotorB1, HIGH);
  digitalWrite(pinMotorB2, LOW);
}

// Set motor L speed
void setLeftMotorSpeed() {
  analogWrite(pinSpeedMotorB, motorSpeedB);
}
// Set motor R speed
void setRightMotorSpeed() {
  analogWrite(pinSpeedMotorA, motorSpeedA);
}
