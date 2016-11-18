#pragma once
#ifndef DIGITAL_DEVICE_H
#define DIGITAL_DEVICE_H
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class DigitalDevice {
private:
	enum status { FINISHED = 0, IN_PROGRESS = 1 };
	enum state { ON = 0, OFF = 1, TRANSIENT = 2, ERROR = 3 };
	string name;
	bool readOnly; // nema komandovanja i onda nema outaddreses
	short inAddresses[2]; // da li se desio
	short outAddresses[2]; //odkomandovao, ocilovi kojima se komanduje
	state state;     //on, off, transient i errror
	char command[2]; //salji npr 01 na out adreses
	status status;
public:
	string getName() { return name; }
	int getState() { return state; }
	int getStatus() { return status; }
	int getReadOnly() { return readOnly; }
	int getInAddress1() { return inAddress1; }
	int getInAddress2() { return inAddress2; }
	int getOutAddress1() { return outAddress1; }
	int getOutAddress2() { return outAddress2; }

	void setName(string newName) { name = newName; }
	void setState(int newState) { state = newState; }
	void setStatus(int newStatus) { status = newStatus; }
	void setReadOnly(int newRead) { readOnly = newRead; }
	void setInAddress1(int newInAddress1) { inAddress1 = newInAddress1; }
	void setInAddress2(int newInAddress2) { inAddress2 = newInAddress2; }
	void setOutAddress1(int newOutAddress1) { outAddress1 = newOutAddress1; }
	void setOutAddress2(int newOutAddress2) { outAddress2 = newOutAddress2; }
	//void setCommand(char* newCommand) { *command = *newCommand; }

	DigitalDevice() {}

	DigitalDevice(string m_name, int m_readOnly, int m_inAddress1, int m_inAddress2, int m_outAddress1, int m_outAddress2, int m_status) :
		name(m_name), readOnly(m_readOnly), inAddress1(m_inAddress1), inAddress2(m_inAddress2), outAddress1(m_outAddress1), outAddress2(m_outAddress2), status(m_status) {
	}

	~DigitalDevice() {}

};


#endif // ! DIGITAL_DEVICE_H