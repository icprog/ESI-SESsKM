#pragma once
#ifndef DIGITAL_DEVICE_H
#define DIGITAL_DEVICE_H
#include <iostream>
#include <ctime>
#include "State.h"

class DigitalDevice {

	std::string name;
	State state; // 00 01 
	int status;
	int readOnly; // nema komandovanja i onda nema outaddreses
	char inAddresses[2]; // da li se desio
	char outAddresses[2]; //odkomandovao, ocilovi kojima se komanduje
	char command[2]; //salji nopr 01 na out adreses
public:
	DigitalDevice() {}
	~DigitalDevice() {}

};


#endif // ! DIGITAL_DEVICE_H