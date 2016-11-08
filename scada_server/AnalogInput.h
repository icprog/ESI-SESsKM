#pragma once
#ifndef ANALOG_INPUT_H
#define ANALOG_INPUT_H
#include <iostream>
#include <ctime>
#include "EngineeringUnit.h"
class AnalogInput {

protected:
	std::string name;
	unsigned short address;
	int EGUMin;
	int EGUMax;
	int EGU;
	int RawMin;
	int RawMax;
	int Raw;
	int value;
	int status;
	char* timeStamp;
	EngineeringUnit eu;
public:
	AnalogInput(std::string m_name, unsigned short m_address,
		int m_EGUMin, int m_EGUMax, int m_EGU, int m_RawMin, int m_RawMAx,
		int m_Raw, int m_value, int m_status, char *m_timeStamp, EngineeringUnit m_eu) :
		name(m_name), address(m_address), EGUMin(m_EGUMin), EGUMax(m_EGUMax), EGU(m_EGU), RawMin(m_RawMin), RawMax(m_RawMAx),
		Raw(m_Raw), value(m_value), status(m_status), timeStamp(m_timeStamp), eu(m_eu) { }
	~AnalogInput() {
		
	}

};


#endif // ! ANALOG_INPUT_H