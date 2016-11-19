#pragma once
#ifndef  ENGINEERING_UNIT_H
#define ENGINEERING_UNIT_H
#include <iostream>

class EngineeringUnit {
public:
	EngineeringUnit(int m_id, std::string m_name, std::string m_sign) : id(m_id), name(m_name), sign(m_sign) {}
	EngineeringUnit() {}

	int getId() const { return id; }
	void setId(int newId) { id = newId; }

	std::string getName() const { return name; }
	void setName(std::string newName) { name = newName; }

	std::string getSign() const { return sign; }
	void setSign(std::string newSign) { sign = newSign; }
private:
	int id;
	std::string name;
	std::string sign;

};


#endif // ! ENGINEERING_UNIT_H