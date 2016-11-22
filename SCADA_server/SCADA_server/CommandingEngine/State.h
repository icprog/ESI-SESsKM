#pragma once
#ifndef STATE_H
#define STATE_H
#include "Context.h"
class State {

public:
	virtual void turnOn(Context *c) {}
	virtual void turnedOn(Context *c) {}
	virtual void turnOff(Context *c) {}
	virtual void turnedOff(Context *c) {}
	virtual void alarm(Context *c) {}
	virtual void error(Context *c) {}
	virtual void idle(Context *c) {}
};

#endif // !STATE_H
