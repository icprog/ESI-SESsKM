#pragma once
#ifndef  ISTATE_H
#define ISTATE_H
#include <iostream>

class IState {

public:
	virtual void handle() = 0;
};


#endif // ! ISTATE_H