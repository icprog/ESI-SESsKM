#pragma once
#ifndef ANALOG_OUTPUT_H
#define ANALOG_OUTPUT_H
#include <iostream>
#include <ctime>
#include "AnalogInput.h"
class AnalogOutput : public AnalogInput {


public:
	AnalogOutput() {}
	AnalogOutput(std::string m_name, short m_address, double m_EGUMin, double m_EGUMax, short m_rawMin, short m_rawMax, short m_raw, double m_value, char m_status) :
	AnalogInput(m_name, m_address, m_EGUMin, m_EGUMax, m_rawMin, m_rawMax, m_raw, m_value, m_status) {}

	/*AnalogOutput(string m_name, unsigned short m_address,
		int m_EGUMin, int m_EGUMax, int m_EGU, int m_RawMin, int m_RawMAx,
		int m_Raw, int m_value, int m_status, char *m_timeStamp, EngineeringUnit m_eu, int m_EGUSetpoint, time_t m_setpointTimeout) :
		AnalogInput(m_name, m_address, m_EGUMin, m_EGUMax, m_EGU, m_RawMin, m_RawMAx, m_Raw, m_value, m_status, m_timeStamp, m_eu),
		EGUSetpoint(m_EGUSetpoint), setpointTimeout(m_setpointTimeout) { } */
	~AnalogOutput() {  }

	int getEGUSetpoint() { return EGUSetpoint; }
	time_t getsetpointTimeout() { return setpointTimeout; }
	void setEGUsetpoint(int newEGUsetpoint) { EGUSetpoint = newEGUsetpoint; }
	void setSetPointTimeout(time_t newSetPoint) { setpointTimeout = newSetPoint; }

private:
	int EGUSetpoint;
	time_t setpointTimeout;
};


#endif // ! ANALOG_OUTPUT_H