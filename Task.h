#ifndef TASK_H
#define TASK_H

bool stateIsTerminal(const State &state);

int reward(const State &state, const Action action, const State &statePrime);
#endif
