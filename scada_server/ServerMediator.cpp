#include "stdafx.h"
#include "ServerMediator.h"
#include <iostream>
template<typename Base, typename T>
bool instanceof(const T*ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

void ServerMediator::callEngine(IComponent *component) {
	if (instanceof<PollEngine>(component)) {
		std::cout << "Test" << std::endl;
		component->notifyMediator();
	}
	
}
