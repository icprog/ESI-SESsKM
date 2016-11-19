#pragma once
#ifndef DIGITAL_DEVICE_H
#define DIGITAL_DEVICE_H
#include <iostream>
#include <string>
#include <ctime>

class DigitalDevice {
public:
	static enum status { FINISHED = 0, IN_PROGRESS = 1 };
	static enum state { ON = 0, OFF = 1, TRANSIENT = 2, ERR = 3 };
private:
	std::string name;
	bool readOnly; // nema komandovanja i onda nema outaddreses
	short inAddresses[2]; // da li se desio
	short outAddresses[2]; //odkomandovao, ocilovi kojima se komanduje
	state state;     //on, off, transient i errror
	char command[2]; //salji npr 01 na out adreses
	status status;

public:
	
	DigitalDevice() {}
	DigitalDevice(std::string m_name, bool m_readOnly, short m_inAddresses[2], short m_outAddresses[2]) : name(m_name), readOnly(m_readOnly) {
		inAddresses[0] = m_inAddresses[0];
		inAddresses[1] = m_inAddresses[1];
		outAddresses[0] = m_outAddresses[0];
		outAddresses[1] = m_outAddresses[1];
	}
	DigitalDevice(std::string m_name, bool m_readOnly, short m_inAddresses[2], short m_outAddresses[2], enum status m_status) :  status(m_status) {
		DigitalDevice(m_name, m_readOnly, m_inAddresses, m_outAddresses);
	}

	~DigitalDevice() {}

	std::string getName() const { return name; }
	enum state getState() const { return state; }
	enum status getStatus() const { return status; }
	bool getReadOnly() const { return readOnly; }
	short *getInAddresses() { return inAddresses; }
	short *getOutAddresses() { return outAddresses; }
	char *getCommand() { return command; }

	void setName(std::string newName) { name = newName; }
	void setState(enum state newState) { state = newState; }
	void setStatus(enum status newStatus) { status = newStatus; }
	void setReadOnly(bool newRead) { readOnly = newRead; }
	void setInAddresses(short newInAddrresses[2]) { inAddresses[0] = newInAddrresses[0]; inAddresses[1] = newInAddrresses[1]; }
	void setOutAddresses(short newOutAddrresses[2]) { outAddresses[0] = newOutAddrresses[0]; outAddresses[1] = newOutAddrresses[1]; }
	void setCommand(short newCommand[2]) { command[0] = newCommand[0]; command[1] = newCommand[1]; }

};


#endif // ! DIGITAL_DEVICE_H