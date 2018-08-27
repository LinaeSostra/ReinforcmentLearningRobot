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
const int locationWidth = 5;

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

char getGridCharacter(const Position &position) {
	bool isRobotLocation = currentState.position == position;
	bool isStartLocation = START_LOCATION == position;
	bool isEndLocation = END_LOCATION == position;

	if(isRobotLocation) { return robotLocation; }
	else if(isStartLocation) { return startLocation; }
	else if(isEndLocation) { return endLocation; }
	return otherLocation;
}

void drawGrid(State state) {
	updateRobotLocation(state.angle);
	char gridChar;
	for (int xPosition = MIN_POSITION; xPosition <= MAX_POSITION; xPosition++) {
		for (int yPosition = MIN_POSITION; yPosition <= MAX_POSITION; yPosition++) {
			Position pos = {xPosition, yPosition};
			gridChar = getGridCharacter(pos);
			cout << setw(locationWidth) << setfill(separator) << gridChar;
		}
		cout << "\n";
	}
	cout << endl;
	//cin.get();
}