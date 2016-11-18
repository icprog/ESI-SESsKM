#pragma once
#ifndef  POLL_ENGINE_H
#define POLL_ENGINE_H
#include "stdafx.h"
class PollEngine {
public:
	PollEngine() {}
	PollEngine(std::vector<char *> *vector_) : vector(vector_) {
	}
	~PollEngine() {
		delete vector, vector = 0;
	}

	void setVector(std::vector<char *> *vector_);
	std::vector<char *> *getVector();
	void sendRequests();

private:
	std::vector<char *> *vector;
	// TCPDriver::getInstance();


};
#endif // ! POLL_ENGINE_H