#pragma once
#ifndef  ENGINEERING_UNIT_H
#define ENGINEERING_UNIT_H
#include <iostream>

class EngineeringUnit {
	int id;
	std::string name;
	std::string sign;

public:

	int getId() const;
	void setId(int id);

	std::string getName() const;
	void setName(std::string name);

	std::string getSign() const;
	void setSign(std::string sign);

	EngineeringUnit(int m_id, std::string m_name, std::string m_sign) : id(m_id), name(m_name), sign(m_sign){}
	EngineeringUnit() {}
};


#endif // ! ENGINEERING_UNIT_H