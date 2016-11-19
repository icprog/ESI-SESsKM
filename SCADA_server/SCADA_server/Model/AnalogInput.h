#pragma once
#ifndef ANALOG_INPUT_H
#define ANALOG_INPUT_H
#include <iostream>
#include <ctime>
#include "EngineeringUnit.h"
class AnalogInput {
public:
	AnalogInput() {}
	AnalogInput(std::string m_name) : name(m_name) {}
	AnalogInput(std::string m_name, short m_address, double m_EGUMin, double m_EGUMax, short m_rawMin, short m_rawMax, short m_raw, double m_value, char m_status) : name(m_name), address(m_address),
		EGUMin(m_EGUMin), EGUMax(m_EGUMax), RawMin(m_rawMin), RawMax(m_rawMax), Raw(m_raw), value(m_value), status(m_status) {}
	~AnalogInput() {
		delete egu, egu = 0;
	}

	std::string getName() const { return name; }
	short getAddress() const { return address; }
	short getRaw() const { return Raw; }
	short getRawMin() const { return RawMin; }
	short getRawMax() const { return RawMax; }
	EngineeringUnit *getEGU() const { return egu; }
	double getEGUMax() const { return EGUMax; }
	double getEGUMin() const { return EGUMin; }
	int getStatus() const { return status; }
	double getValue() const { return value; }

	void setName(std::string newName) { name = newName; }
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
	std::string name;
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