#pragma once
#ifndef ALARM_H
#define ALARM_H
#include <iostream>
#include <ctime>
#include <string>
class Alarm {
public:
	Alarm() {}
	Alarm(std::string m_name, time_t m_time) : name(m_name), timeStamp(m_time) {}
	~Alarm() {}

	time_t getTime() const { return timeStamp; }
	std::string getName() const { return name; }
	void setTime(time_t newTime) { timeStamp = newTime; }
	void setName(std::string newName) { name = newName; }
	bool getConfirmed() const { return confirmed; }
	void setConfirmed(bool conf) { confirmed = conf;  }
	short getAddress() const { return address; }
	void setAddress(short add) { address = add; }
	std::string getMessage() const { return message; }
	void setMessage(std::string mes) { message = mes; }
private:
	time_t timeStamp;
	std::string name;
	bool confirmed;
	short address;
	std::string message;
};


#endif // ! ALARM_H