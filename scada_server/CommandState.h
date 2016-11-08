#pragma once
#ifndef  COMMAND_STATE_H
#define COMMAND_STATE_H
#include <iostream>
#include "IState.h"

class CommandState : IState {
public:
	static IState *instance();
};


#endif // ! CONTEXT_H