#pragma once
#ifndef  POLL_ENGINE_H
#define POLL_ENGINE_H
#include "stdafx.h"
class PollEngine {
public:
	PollEngine() {}
	PollEngine(std::vector<char *> *vector_, Buffer *sharedBuffer_) : vector(vector_), sharedBuffer(sharedBuffer_) {
		std::thread pollEngineThread(PollEngine::sendRequests, this);
		pollEngineThread.detach();
	}
	~PollEngine() {
		delete vector, vector = 0;
		delete response, response = 0;
	}

	void setVector(std::vector<char *> *vector_);
	std::vector<char *> *getVector();
	static void sendRequests(PollEngine *that);
	Buffer *getSharedBuffer() { return sharedBuffer; }
	char *getResponse() { return response; }
	int getResponseSize() { return *(int *)response; }
private:
	std::vector<char *> *vector;
	char *response = nullptr;
	Buffer *sharedBuffer;
	// TCPDriver::getInstance();


};
#endif // ! POLL_ENGINE_H