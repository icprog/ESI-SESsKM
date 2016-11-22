#pragma once
#ifndef TURN_ON_H
#define TURN_ON_H
#include "State.h"
#include "TurnedOn.h"
#include "Alarm.h"
class TurnOn : public State {

public:
	void turnedOn(Context *c);

};

#endif // !TURN_ON_H
