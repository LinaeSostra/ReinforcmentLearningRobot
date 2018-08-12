#ifndef ROBOT_H
#define ROBOT_H

void resetPosition(); // Reset robot to starting location
void resetToRandomPosition(); // Reset robot to random starting location
void logState(); // Save the robot's state
void apply(Action action); // Adjust the robot's states
#endif
