#pragma once
#ifndef  POLL_ENGINE_H
#define POLL_ENGINE_H
#include "stdafx.h"
class PollEngine {
public:
	PollEngine() {}
	PollEngine(std::vector<char *> *vector_) : vector(vector_) {
		std::thread pollEngineThread(PollEngine::sendRequests, this);
		pollEngineThread.detach();
	}
	~PollEngine() {
		delete vector, vector = 0;

	}

	void setVector(std::vector<char *> *vector_);
	std::vector<char *> *getVector();
	static void sendRequests(PollEngine *that);
private:
	std::vector<char *> *vector;

	// TCPDriver::getInstance();


};
#endif // ! POLL_ENGINE_H