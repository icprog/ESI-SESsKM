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

void PollEngine::sendRequests(PollEngine *that)
{
	//while (1) {
		for (int i = 0; i < that->vector->size(); i++) {
			char *request = new char[12];
			TCPDriver::getInstance().createRequest(that->vector->at(i), request);

			TCPDriver::getInstance().sendRequest(request);


		}
		//Sleep(2000);
	//}
}
