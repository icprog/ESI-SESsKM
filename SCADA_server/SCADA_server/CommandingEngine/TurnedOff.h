#pragma once
#ifndef TURNED_OFF_H
#include "State.h"
#include "../Model/DigitalDevice.h"
#include "TurnOn.h"
class TurnedOff : public State {
public:
	void turnOn(Context *c);
};
#endif // !TURNED_ON_H
