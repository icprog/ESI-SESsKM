#pragma once
#ifndef ANALOG_INPUT_H
#define ANALOG_INPUT_H
#include <iostream>
#include <ctime>
#include "EngineeringUnit.h"
using namespace std;
class AnalogInput {
public:
	AnalogInput() {}
	~AnalogInput() {
		delete egu, egu = 0;
	}

	string getName() { return name; }
	short getAddress() { return address; }
	short getRaw() { return Raw; }
	short getRawMin() { return RawMin; }
	short getRawMax() { return RawMax; }
	EngineeringUnit *getEGU() { return &egu; }
	double getEGUMax() { return EGUMax; }
	double getEGUMin() { return EGUMin; }
	int getStatus() { return status; }
	double getValue() { return value; }

	void setName(string newName) { name = newName; }
	void setAddress(short newAddress) { address = newAddress; }
	void setRaw(short newRaw) { Raw = newRaw; }
	void setRawMin(short newRawMin) { RawMin = newRawMin; }
	void setRawMax(short newRawMax) { RawMin = newRawMax; }
	void setEGU(EngineeringUnit *egu_) { egu = egu_; }
	void setEGUMin(double newEGUMin) { EGUMin = newEGUMin; }
	void setEGUMax(double newEGUMax) { EGUMax = newEGUMax; }
	void setValue(double newValue) { value = newValue; }
	void setStatus(int newStatus) { status = newStatus; }


protected:
	string name;
	short address;
	double EGUMin;
	double EGUMax;
	short RawMin;
	short RawMax;
	short Raw;
	double value;
	char status;
	time_t timeStamp;
	EngineeringUnit *egu;

};


#endif // ! ANALOG_INPUT_H