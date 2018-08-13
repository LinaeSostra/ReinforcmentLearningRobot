#include "Learning.h"
#include "Robot.h"
#include "Task.h"
#include "Strings.h"
#include <iostream>

// This code is to run simulation the Semi-gradient RL algorithm
// for 50 episodes to verify the algorithm works as intended, and
// then for verfication to be placed on the firmwire of Benny and Bunny

// Heavy Reference of Nick S Walker's Arduino RL code was used while 
// writing this coding:
// https://github.com/nickswalker/ArduinoRL/blob/master/TwoJoint/TwoJoint.ino

#define EVALUATION_MODE 1
#define EVALUATION_SWITCH_POINT 50
#define EVALUATION_MAX_STEPS 200

// Variables
extern State currentState;
extern State previousState;

Action nextAction = Stay;

float lastReward = 0.0;

int32_t cumulativeReward = 0.0;
uint32_t currentEpisodeStep = 0;
uint16_t currentEpisode = 0;

void logStepInformation() {
	cout << "\n" << currentEpisodeStep << " , " << cumulativeReward;
}

void markEpisodeStart() {
	cout << "\n!!!";
}

void markEpisodeEnd() {
	cout << "\n***";
}

void completedLearning() {
	cout << "\nFinished RL Learning after 50 episodes";
}

void restartEpisode() {
	resetToRandomPosition();
	cumulativeReward = 0.0;
	currentEpisodeStep = 0;
	markEpisodeEnd();
	currentEpisode += 1;
}


int main() {
	bool stillLearning = true;
	while(stillLearning) {
		//Populates current and previous state for us
		apply(nextAction);

		// Log values from firmwire here, but not applicable in simulation

		// TODO(Rebecca): I don't think this comment is correct
		// RL algorithm populates next action for us
		Action previousAction = nextAction;
		update(previousState, previousAction, currentState);

		// Update & Log progress of episode
		currentEpisodeStep += 1;
		cumulativeReward += lastReward;
		logStepInformation();

		// Start new episode if agent meets terminal conditions
		bool reachedMaxEpisodeSteps = currentEpisodeStep > EVALUATION_MAX_STEPS;
		if(stateIsTerminal(currentState) || reachedMaxEpisodeSteps) {
			restartEpisode();
			// If enough episodes were conducted, stop learning
			bool finishedLearning = EVALUATION_MODE && currentEpisode > EVALUATION_SWITCH_POINT;
			if(finishedLearning) {
				stillLearning = false;
			} else {
				markEpisodeStart();
			}
		}
	}
	completedLearning();
}