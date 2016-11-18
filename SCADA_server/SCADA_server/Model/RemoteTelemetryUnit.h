#pragma once
#ifndef  RemoteTelemetryUnit_H
#define RemoteTelemetryUnit_H
#include <iostream>
#include <vector>
#include "AnalogInput.h"
#include "AnalogOutput.h"
#include "DigitalDevice.h"

class RemoteTelemetryUnit {
public:
	std::string id;
	std::string industrialProtocol;
	std::string transportProtocol;
	std::string ipAddress;
	int port;
	int analogInputNum;
	int analogOutputNum;
	int digitalInputNum;
	int digitalOutputNum;

	std::vector<AnalogInput> analogInputs;
	std::vector<AnalogOutput> analogOutputs;
	std::vector<DigitalDevice> digitalDevices;
public:
	RemoteTelemetryUnit() {}
	RemoteTelemetryUnit(std::string id, std::string m_industrialProtocol, std::string m_transportProtocol, std::string m_ipAddress, int m_port, int m_analogInputNum,
		int m_analogOutputNum, int m_digitalInputNum, int m_digitalOutputNum,
		std::vector<AnalogInput> m_analogInputs, std::vector<AnalogOutput> m_analogOutputs, std::vector<DigitalDevice> m_digitalDevices
	) : id(id), industrialProtocol(m_industrialProtocol), transportProtocol(m_transportProtocol), ipAddress(m_ipAddress), port(m_port),
		analogInputNum(m_analogInputNum), analogOutputNum(m_analogOutputNum), digitalInputNum(m_digitalInputNum), digitalOutputNum(m_digitalOutputNum),
		analogInputs(m_analogInputs), analogOutputs(m_analogOutputs), digitalDevices(m_digitalDevices)
	{}

	string getId() { return id; }
	string getIndProt() { return industrialProtocol; }
	string getTransProt() { return transportProtocol; }
	string getIpAddress() { return ipAddress; }
	unsigned short getPort() { return port; }
	int getAnalogInputNum() { return analogInputNum; }
	int getAnalogOutputNum() { return analogOutputNum; }
	int getDigitalInputNum() { return digitalInputNum; }
	int getDigitalOutputNum() { return digitalOutputNum; }
	vector<AnalogInput> getAnalogInputs() { return analogInputs; }
	vector<AnalogOutput> getAnalogOutputs() { return analogOutputs; }
	vector<DigitalDevice> getDigitalDevices() { return digitalDevices; }

	void setId(string newName) { id = newName; }
	void setIndProt(string newIndProt) { industrialProtocol = newIndProt; }
	void setTransProt(string newTransProt) { transportProtocol = newTransProt; }
	void setIpAddress(string newIpAddress) { ipAddress = newIpAddress; }
	void setPort(unsigned short newPort) { port = newPort; }

	~RemoteTelemetryUnit() {
		delete &analogInputs;
		delete &analogOutputs;
		delete &digitalDevices;
	}

};



#endif // ! RTU_H