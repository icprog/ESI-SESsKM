#pragma once
#ifndef  RTU_H
#define RTU_H
#include <iostream>
#include <vector>
#include "AnalogInput.h"
#include "AnalogOutput.h"
#include "DigitalDevice.h"

class RTU {
	int id;
	std::string industrialProtocol;
	std::string transportProtocol;
	char *ipAddress;
	unsigned short port;
	int analogInputNum;
	int analogOutputNum;
	int digitalInputNum;
	int digitalOutputNum;

	std::vector<AnalogInput> *analogInputs;
	std::vector<AnalogInput> *analogOutputs;
	std::vector<AnalogInput> *digitalDevices;
public:
	RTU(int id, std::string m_industrialProtocol, std::string m_transportProtocol, char* m_ipAddress, unsigned short m_port, int m_analogInputNum,
		int m_analogOutputNum, int m_digitalInputNum, int m_digitalOutputNum,
		std::vector<AnalogInput> *m_analogInputs, std::vector<AnalogInput> *m_analogOutputs, std::vector<AnalogInput> *m_digitalDevices
	) : id(id), industrialProtocol(m_industrialProtocol), transportProtocol(m_transportProtocol), ipAddress(m_ipAddress), port(m_port),
		analogInputNum(m_analogInputNum), analogOutputNum(m_analogOutputNum), digitalInputNum(m_digitalInputNum), digitalOutputNum(m_digitalOutputNum),
		analogInputs(m_analogInputs), analogOutputs(m_analogOutputs), digitalDevices(m_digitalDevices)
		{}
	~RTU() {
		delete analogInputs, analogInputs = 0;
		delete analogOutputs, analogOutputs = 0;
		delete digitalDevices, digitalDevices = 0;
	}

};



#endif // ! RTU_H