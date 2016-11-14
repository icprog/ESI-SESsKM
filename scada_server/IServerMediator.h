#pragma once
#ifndef  ISERVER_MEDIATOR_H
#define ISERVER_MEDIATOR_H
#include "IComponent.h"
class IServerMediator {

public:
	virtual void callEngine(IComponent *component) = 0;
	virtual ~IServerMediator() {}
};

#endif // ! ISERVER_MEDIATOR_H