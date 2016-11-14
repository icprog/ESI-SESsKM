#pragma once
#ifndef  SERVER_MEDIATOR_H
#define SERVER_MEDIATOR_H
#include "IComponent.h"
#include "IServerMediator.h"

class ServerMediator : public IServerMediator {
public:

	void callEngine(IComponent *component);

};

#endif // ! COMPONENT_MEDIATOR_H