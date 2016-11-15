#pragma once
#ifndef ANALOG_INPUT_H
#define ANALOG_INPUT_H
#include <iostream>
#include <ctime>
#include "EngineeringUnit.h"
using namespace std;
class AnalogInput {

protected:
	std::string name;
	int address;
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

	string getName() { return name; }
	int getAddress() { return address; }
	int getRaw() { return Raw; }
	int getRawMin() { return RawMin; }
	int getRawMax() { return RawMax; }
	int getEGU() { return EGU; }
	int getEGUMax() { return EGUMax; }
	int getEGUMin() { return EGUMin; }
	int getStatus() { return status; }
	int getValue() { return value; }

	void setName(string newName) { name = newName; }
	void setAddress(int newAddress) { address = newAddress; }
	void setRaw(int newRaw) { Raw = newRaw; }
	void setRawMin(int newRawMin) { RawMin = newRawMin; }
	void setRawMax(int newRawMax) { RawMin = newRawMax; }
	void setEGU(int newEGU) { EGU = newEGU; }
	void setEGUMin(int newEGUMin) { EGU = newEGUMin; }
	void setEGUMax(int newEGUMax) { EGU = newEGUMax; }
	void setValue(int newValue) { value = newValue; }
	void setStatus(int newStatus) { status = newStatus; }

	AnalogInput(std::string m_name, int m_address,
		int m_EGUMin, int m_EGUMax, int m_EGU, int m_RawMin, int m_RawMAx,
		int m_Raw, int m_value, int m_status, char *m_timeStamp, EngineeringUnit m_eu) :
		name(m_name), address(m_address), EGUMin(m_EGUMin), EGUMax(m_EGUMax), EGU(m_EGU), RawMin(m_RawMin), RawMax(m_RawMAx),
		Raw(m_Raw), value(m_value), status(m_status), timeStamp(m_timeStamp), eu(m_eu) { }

	AnalogInput(std::string m_name, int m_address,
		int m_EGUMin, int m_EGUMax, int m_EGU, int m_RawMin, int m_RawMAx,
		int m_Raw, int m_value) :
		name(m_name), address(m_address), EGUMin(m_EGUMin), EGUMax(m_EGUMax), EGU(m_EGU), RawMin(m_RawMin), RawMax(m_RawMAx),
		Raw(m_Raw), value(m_value) { }
	AnalogInput() {}

	~AnalogInput() {
		
	}

};


#endif // ! ANALOG_INPUT_H