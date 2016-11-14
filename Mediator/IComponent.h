#pragma once
#ifndef  ICOMPONENT_MEDIATOR_H
#define ICOMPONENT_MEDIATOR_H

class IComponent {

public:
	virtual void notifyMediator() = 0;
	virtual ~IComponent() {}
};

#endif // ! ICOMPONENT_MEDIATOR_H