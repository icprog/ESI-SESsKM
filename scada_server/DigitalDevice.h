#pragma once
#ifndef DIGITAL_DEVICE_H
#define DIGITAL_DEVICE_H
#include <iostream>
#include <ctime>

class DigitalDevice {

	std::string name;
	int status;
	int readOnly; // nema komandovanja i onda nema outaddreses
	int inAddress1;
	int inAddress2;
	int outAddress1;
	int outAddress2;
	//char inAddresses[2]; // da li se desio
	//char outAddresses[2]; //odkomandovao, ocilovi kojima se komanduje
	char state;
	char command[2]; //salji nopr 01 na out adreses
public:
	string getName() { return name; }
	char getState() { return state; }
	int getStatus() { return status; }
	int getReadOnly() { return readOnly; }
	int getInAddress1() { return inAddress1; }
	int getInAddress2() { return inAddress2; }
	int getOutAddress1() { return outAddress1; }
	int getOutAddress2() { return outAddress2; }

	void setName(string newName) { name = newName; }
	void setState(char newState) { state = newState; }
	void setStatus(int newStatus) { status = newStatus; }
	void setReadOnly(int newRead) { readOnly = newRead; }
	void setInAddress1(int newInAddress1) { inAddress1 = newInAddress1; }
	void setInAddress2(int newInAddress2) { inAddress2 = newInAddress2; }
	void setOutAddress1(int newOutAddress1) { outAddress1 = newOutAddress1; }
	void setOutAddress2(int newOutAddress2) { outAddress2 = newOutAddress2; }

	DigitalDevice() {}

	DigitalDevice(std::string m_name, int m_readOnly, int m_inAddress1, int m_inAddress2, int m_outAddress1, int m_outAddress2, int m_status, char m_state) :
		name(m_name), readOnly(m_readOnly), inAddress1(m_inAddress1), inAddress2(m_inAddress2), outAddress1(m_outAddress1), outAddress2(m_outAddress2), status(m_status), state(m_state)  {}

	~DigitalDevice() {}

};


#endif // ! DIGITAL_DEVICE_H