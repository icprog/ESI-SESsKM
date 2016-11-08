#pragma once
#ifndef  CONTEXT_H
#define CONTEXT_H
#include <iostream>
#include "IState.h"

class Context { 
	friend class IState;
	IState *state;
	void changeState(IState *);
public:
	void handle();
};


#endif // ! CONTEXT_H