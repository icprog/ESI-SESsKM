#pragma once
#ifndef ALARM_H
#define ALARM_H
#include <iostream>
#include <ctime>
#include <string>
using namespace std;
class Alarm {
public:
	Alarm() {}
	Alarm(string m_name, time_t m_time) : name(m_name), timeStamp(m_time) {}
	~Alarm() {}

	time_t getTime() const { return timeStamp; }
	string getName() const { return name; }
	void setTime(time_t newTime) { timeStamp = newTime; }
	void setName(string newName) { name = newName; }
	bool getConfirmed() const { return confirmed; }
	void setConfirmed(bool conf) { confirmed = conf;  }

private:
	time_t timeStamp;
	string name;
	bool confirmed;


};


#endif // ! ALARM_H