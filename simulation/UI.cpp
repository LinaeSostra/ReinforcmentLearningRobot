// Draws the map of the environnment, where the robot is in the mapping
#include <iostream>
#include <iomanip>
#include "Main.h"

using namespace std;

//TODO(Rebecca): May need to reformat to match code elsewhere
const char separator = ' ';
const char startLocation = 'O';
const char endLocation = 'X';
const char otherLocation = '.';
const int locationWidth = 3;

char robotLocation = '^';

void updateRobotLocation(Angle angle) {
	switch(angle) {
		case North:
			robotLocation = '^';
			break;
		case East:
			robotLocation = '>';
			break;
		case South:
			robotLocation = 'v';
			break;
		case West:
			robotLocation = '<';
			break;
	}
}

char getGridCharacter(int xPosition, int yPosition) {
	bool isRobotLocation = (xPosition == currentState.xPosition) && (yPosition == currentState.yPosition);
	bool isStartLocation = (xPosition == START_POSITION) && (yPosition == START_POSITION);
	bool isEndLocation = (xPosition == END_POSITION) && (yPosition == END_POSITION);

	if(isRobotLocation) { return robotLocation; }
	else if(isStartLocation) { return startLocation; }
	else if(isEndLocation) { return endLocation; }
	return otherLocation;
}

void drawGrid(State state) {
	updateRobotLocation(state.angle);
	char gridChar;
	for (int xPosition = MIN_POSITION; xPosition < MAX_POSITION; xPosition++) {
		for (int yPosition = MIN_POSITION; yPosition < MAX_POSITION; yPosition++) {
			gridChar = getGridCharacter(xPosition, yPosition);
			cout << setw(locationWidth) << setfill(separator) << gridChar;
		}
		cout << "\n";
	}
	cout << endl;
	//cin.get();
}