#pragma once
#ifndef TURN_OFF_H
#include "State.h"
#include "../Model/DigitalDevice.h"
#include "Alarm.h"
#include "TurnedOff.h"
class TurnOff : public State {
public:
	void turnedOff(Context *c);
};
#endif // !TURNED_ON_H
