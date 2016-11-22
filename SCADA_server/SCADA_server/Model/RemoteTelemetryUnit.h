#pragma once
#ifndef  RemoteTelemetryUnit_H
#define RemoteTelemetryUnit_H
#include <iostream>
#include <vector>
#include "AnalogInput.h"
#include "AnalogOutput.h"
#include "DigitalDevice.h"
#include "Alarm.h"

class RemoteTelemetryUnit {
private:
	std::string id;
	std::string industrialProtocol;
	std::string transportProtocol;
	std::string ipAddress;
	int port;
	int analogInputNum;
	int analogOutputNum;
	int digitalInputNum;
	int digitalOutputNum;

	std::vector<AnalogInput*> analogInputs;
	std::vector<AnalogOutput*> analogOutputs;
	std::vector<DigitalDevice*> digitalDevices;
	std::vector<Alarm> *alarms;
public:
	RemoteTelemetryUnit() {}

	RemoteTelemetryUnit(std::string m_id, std::string m_industrialProtocol, std::string m_transportProtocol, std::string m_ipAddress, int m_port, int m_analogInputNum,
		int m_analogOutputNum, int m_digitalInputNum, int m_digitalOutputNum,
		std::vector<AnalogInput*> m_analogInputs, std::vector<AnalogOutput*> m_analogOutputs, std::vector<DigitalDevice*> m_digitalDevices
	) : id(m_id), industrialProtocol(m_industrialProtocol), transportProtocol(m_transportProtocol), ipAddress(m_ipAddress), port(m_port),
		analogInputNum(m_analogInputNum), analogOutputNum(m_analogOutputNum), digitalInputNum(m_digitalInputNum), digitalOutputNum(m_digitalOutputNum),
		analogInputs(m_analogInputs), analogOutputs(m_analogOutputs), digitalDevices(m_digitalDevices) 
	{
		alarms = new std::vector<Alarm>;
	}

	/*RemoteTelemetryUnit(std::string m_id, std::string m_industrialProtocol, std::string m_transportProtocol, std::string m_ipAddress, int m_port, int m_analogInputNum,
		int m_analogOutputNum, int m_digitalInputNum, int m_digitalOutputNum,
		std::vector<AnalogInput>* m_analogInputs, std::vector<AnalogOutput>* m_analogOutputs, std::vector<DigitalDevice> *m_digitalDevices)  {
		RemoteTelemetryUnit(m_id, m_industrialProtocol, m_transportProtocol, m_ipAddress, m_port, m_analogInputNum, m_analogOutputNum, m_digitalInputNum, m_digitalOutputNum, *m_analogInputs,
			*m_analogOutputs, *m_digitalDevices);
		alarms = new std::vector<Alarm>;
	}*/

	~RemoteTelemetryUnit() {

		for (int i = 0; i < digitalDevices.size(); i++) {
			DigitalDevice *it = digitalDevices.at(i);
			delete it;
		}
		for (int i = 0; i < analogInputs.size(); i++) {
			AnalogInput *it = analogInputs.at(i);
			delete it;
		}
		for (int i = 0; i < analogOutputs.size(); i++) {
			AnalogOutput *it = analogOutputs.at(i);
			delete it;
		}
		delete alarms;
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
	std::vector<AnalogInput*> getAnalogInputs() { return analogInputs; }
	std::vector<AnalogOutput*> getAnalogOutputs() { return analogOutputs; }
	std::vector<DigitalDevice*> getDigitalDevices() { return digitalDevices; }
	std::vector<Alarm> *getAlarms() { return alarms; }
	void setId(std::string newName) { id = newName; }
	void setIndProt(std::string newIndProt) { industrialProtocol = newIndProt; }
	void setTransProt(std::string newTransProt) { transportProtocol = newTransProt; }
	void setIpAddress(std::string newIpAddress) { ipAddress = newIpAddress; }
	void setPort(int newPort) { port = newPort; }

};



#endif // ! RTU_H