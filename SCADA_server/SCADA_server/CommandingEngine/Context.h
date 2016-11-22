#pragma once
#ifndef CONTEXT_H
#define CONTEXT_H
#include "State.h"
#include "CommandingEngine.h"
class Context {
	class State* current;
	CommandingEngine *that;
public:
	Context();
	void setCurrent(State *s) {
		current = s;
	}
	void turnOn();
	void turnedOn();
	void turnOff();
	void turnedOff();
	void alarm();
	void error();
	void idle();
	void setCommandingEngine(CommandingEngine *ce) { that = ce; }
	State *getCurrentState() { return current; }
	CommandingEngine *getCommandingEngine() { return that; }
};

#endif // !CONTEXT_H
