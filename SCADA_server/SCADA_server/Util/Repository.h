#pragma once
#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "stdafx.h"
#include "Structure.h"
#include <stack>
#include <mutex>
class Repository {
	std::stack<Structure> *vec;
	std::mutex m;
public:

	Repository() {
		vec = new std::stack<Structure>();
	}
	~Repository() {
		delete vec, vec = 0;
	}
	std::stack<Structure> *getVector() { return vec; }
	void setVector(std::stack<Structure>*m) { vec = m; }
	void add(Structure s);
	void remove(Structure s);
	void get(Structure *s);
};

#endif