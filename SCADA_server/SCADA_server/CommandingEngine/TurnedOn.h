#pragma once
#ifndef TURNED_ON_H
#include "State.h"
#include "TurnOff.h"
#include "../Model/DigitalDevice.h"
class TurnedOn: public State {
public:
	void turnOff(Context *c);
};
#endif // !TURNED_ON_H
