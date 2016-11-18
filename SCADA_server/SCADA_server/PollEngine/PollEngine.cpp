#include "stdafx.h"
#include "PollEngine.h"

void PollEngine::setVector(std::vector<char*>* vector_)
{
	this->vector = vector;
}

std::vector<char*>* PollEngine::getVector()
{
	return this->vector;
}

void PollEngine::sendRequests()
{
	for (int i = 0; i < vector->size; i++) {
		TCPDriver::getInstance().sendRequest(TCPDriver::getInstance().createRequest(vector->at(i)));
	}
}
