#pragma once
#ifndef ALARM_H
#define ALARM_H
#include <iostream>
#include <ctime>
#include <string>
class Alarm {
public:
	Alarm() {}
	Alarm(std::string m_name, time_t m_time, short address_, std::string message_) : name(m_name), timeStamp(m_time),
	address(address_), message(message_)
	{
		confirmed = false;
		corrected = false;
		errorAlarm = false;
	}
	~Alarm() {}

	time_t getTime() const { return timeStamp; }
	std::string getName() const { return name; }
	void setTime(time_t newTime) { timeStamp = newTime; }
	void setName(std::string newName) { name = newName; }
	bool getConfirmed() const { return confirmed; }
	void setConfirmed(bool conf) { confirmed = conf;  }
	bool getCorrected() const { return corrected; }
	void setCorrected(bool corr) { corrected = corr; }
	bool isErrorAlarm() const { return errorAlarm; }
	void setErrorAlarm(bool corr) { errorAlarm = corr; }
	short getAddress() const { return address; }
	void setAddress(short add) { address = add; }
	std::string getMessage() const { return message; }
	void setMessage(std::string mes) { message = mes; }
private:
	time_t timeStamp;
	std::string name;
	bool confirmed;
	bool corrected;
	bool errorAlarm;
	short address;
	std::string message;
};


#endif // ! ALARM_H