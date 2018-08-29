#include "Main.h"
#include <fstream>

using namespace std;

// This code is to run simulation the Semi-gradient RL algorithm
// for 50 episodes to verify the algorithm works as intended, and
// then for verfication to be placed on the firmwire of Benny and Bunny

// Heavy Reference of Nick S Walker's Arduino RL code was used while 
// writing this coding:
// https://github.com/nickswalker/ArduinoRL/blob/master/TwoJoint/TwoJoint.ino

Action nextAction = Up;

double lastReward = 0.0;
double cumulativeReward = 0.0;

int currentRun = 0;
int currentEpisodeStep = 0; 
int currentEpisode = 0;

void logStepInformation() {
	cout << "\n(Current Episode, Cumulative Reward):\t(" << currentEpisodeStep << " , " << cumulativeReward << ")\n";
}

void markEpisodeStart() {
	cout << "\n!!!\n";
}

void markEpisodeEnd() {
	cout << "\n***\n";
}
void markRunStart() {
	cout << "Starting Run " << currentRun << "!!!!\n";
}
void markRunEnd() {
	cout << "\nFinished RL Learning after " << currentEpisode << " episodes\n";
}

void cleanFile(const char* filePath) {
	ofstream file;
	file.open(filePath, ios::out);
}

// Clears all files within Runs folder
void cleanAllFiles() {
	cleanFile("Runs/weights.csv");

	for(unsigned int i = 0; i < NUM_OF_RUNS; i++) {
		string runFilePath = "Runs/run%d.csv", i;
		cout << "Clearing " << runFilePath.c_str() << "\n";
		cleanFile(runFilePath.c_str());
	}
}

void recordEpisodeToFile() {
	string episodeFilePath  = "Runs/run%d.csv", currentRun;
	ofstream file;
	file.open(episodeFilePath.c_str(), ios::app);
	file << currentEpisode << "," << currentEpisodeStep << "," << cumulativeReward << "\n";
}

void recordRunToFile() {
	ofstream file;
	file.open("Runs/weights.csv", ios::app);
	file << currentRun << ",";
	for(unsigned int i = 0; i < NUM_FEATURES-1; i++) {
		file << weights[i] << ",";
	}
	file << weights[i] << "\n";
}

void restartEpisode() {
	recordEpisodeToFile();
	drawGrid(currentState);  // If the  new state is not out of boundaries, update currentState with new state.
	logStepInformation();
	resetPosition();
	cumulativeReward = 0.0;
	currentEpisodeStep = 0;
	markEpisodeEnd();
	currentEpisode += 1;
}

void restartRun() {
	recordRunToFile();
	logWeights();
	cumulativeReward = 0.0;
	currentEpisodeStep = 0;
	currentEpisode = 0;
	currentRun += 1;
}

void setupSeed() {
	srand(time(NULL));
}

int main() {
	cleanAllFiles();
	setupSeed();
	bool stillRunning = true;
	while(stillRunning) {
		bool stillLearning = true;
		while(stillLearning) {
			// Log values from firmwire here, but not applicable in simulation
			if(currentEpisodeStep % EVALUATION_MAX_STEPS == 0 ){
				logState();
				//logWeights();
				//drawGrid(currentState);
			}
			//cout << "~~~~~~~~~~~~~~~~\nCurrent Episode Step:\t" << currentEpisodeStep << "\n";
			//Populates current and previous state for us
			apply(nextAction);
			//cout << "Action Movement: " << nextAction << "\n";
			//cout << "Previous State: (" << previousState.position.x << ", " << previousState.position.y << ", " << previousState.angle << ")" << "\n";
			//cout << "Current State: (" << currentState.position.x << ", " << currentState.position.y << ", " << currentState.angle << ")" << "\n";

			// TODO(Rebecca): I don't think this comment is correct
			// RL algorithm populates next action for us
			Action previousAction = nextAction;
			update(previousState, previousAction, currentState);

			// Update & Log progress of episode
			currentEpisodeStep += 1;
			cumulativeReward += lastReward; 
			//logStepInformation();
			//drawGrid(currentState);

			// Start new episode if agent meets terminal conditions
			bool reachedMaxEpisodeSteps = currentEpisodeStep >= EVALUATION_MAX_STEPS;
			if(stateIsTerminal(currentState) || reachedMaxEpisodeSteps) {
				restartEpisode();
				// If enough episodes were conducted, stop learning
				bool finishedLearning = currentEpisode >= EVALUATION_SWITCH_POINT;
				if(finishedLearning) {
					stillLearning = false;
				} else {
					markEpisodeStart();
				}
			}
		}
		markRunEnd();
		restartRun();
		bool finishedRunning = currentRun >= NUM_OF_RUNS;
		if(finishedRunning) {
			stillRunning = false;
		} else {
			markRunStart();
		}
	}
}