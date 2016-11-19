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

	RemoteTelemetryUnit(std::string m_id, std::string m_industrialProtocol, std::string m_transportProtocol, std::string m_ipAddress, int m_port, int m_analogInputNum,
		int m_analogOutputNum, int m_digitalInputNum, int m_digitalOutputNum,
		std::vector<AnalogInput> m_analogInputs, std::vector<AnalogOutput> m_analogOutputs, std::vector<DigitalDevice> m_digitalDevices
	) : id(m_id), industrialProtocol(m_industrialProtocol), transportProtocol(m_transportProtocol), ipAddress(m_ipAddress), port(m_port),
		analogInputNum(m_analogInputNum), analogOutputNum(m_analogOutputNum), digitalInputNum(m_digitalInputNum), digitalOutputNum(m_digitalOutputNum),
		analogInputs(m_analogInputs), analogOutputs(m_analogOutputs), digitalDevices(m_digitalDevices) {}

	~RemoteTelemetryUnit() {
		delete &analogInputs;
		delete &analogOutputs;
		delete &digitalDevices;
	}

	std::string getId() const { return id; }
	std::string getIndProt() const { return industrialProtocol; }
	std::string getTransProt() const { return transportProtocol; }
	std::string getIpAddress() const { return ipAddress; }
	int getPort() const { return port; }
	int getAnalogInputNum() const { return analogInputNum; }
	int getAnalogOutputNum() const { return analogOutputNum; }
	int getDigitalInputNum() const { return digitalInputNum; }
	int getDigitalOutputNum() const { return digitalOutputNum; }
	std::vector<AnalogInput> getAnalogInputs() { return analogInputs; }
	std::vector<AnalogOutput> getAnalogOutputs() { return analogOutputs; }
	std::vector<DigitalDevice> getDigitalDevices() { return digitalDevices; }

	void setId(std::string newName) { id = newName; }
	void setIndProt(std::string newIndProt) { industrialProtocol = newIndProt; }
	void setTransProt(std::string newTransProt) { transportProtocol = newTransProt; }
	void setIpAddress(std::string newIpAddress) { ipAddress = newIpAddress; }
	void setPort(int newPort) { port = newPort; }

};



#endif // ! RTU_H