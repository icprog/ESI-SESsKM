#include "stdafx.h"
#include "Alarm.h"

void AlarmState::alarm(Context * c)
{

	if (TurnedOn* v = dynamic_cast<TurnedOn*>(c->getCurrentState())) {

		
	}
	
}
