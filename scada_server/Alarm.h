#pragma once
//time_t timeStamp;
//char name[100];
#ifndef ALARM_H
#define ALARM_H
#include <iostream>
#include <ctime>
#include <string>
using namespace std;
class Alarm {

private:
	time_t timeStamp;
	string name;
public:
	time_t getTime() { return timeStamp; }
	string getName() { return name; }
	void setTime(time_t newTime) { timeStamp = newTime; }
	void setName(string newName) { name = newName; }
	Alarm(string m_name, time_t m_time): name(m_name),timeStamp(m_time) {}
	~Alarm() {}

};


#endif // ! ALARM_H
