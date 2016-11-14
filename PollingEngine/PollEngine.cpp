#include "stdafx.h"
#include "PollEngine.h"

void PollEngine::notifyMediator() {
}

int PollEngine::makeConnection(SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, unsigned long int nonBlockingMode)
{
	return tcpdriver->connectt(connectSocket, listenSocket,ipAddress, port, nonBlockingMode);
}

void PollEngine::sendRequests(SOCKET *connectSocket, std::vector<Request*> *requests, char * response, Buffer * buffer, bool closeConnection, unsigned long int nonBlockingMode) {
	int iResult = 0;
	for (int i = 0;i < (*requests).size(); i++) {
		iResult = tcpdriver->sendRequest(connectSocket, (*requests).at(i)->getRequest(), closeConnection, nonBlockingMode);
		receiveResponse(connectSocket, (*requests).at(i)->getRequest(), response, buffer, closeConnection, nonBlockingMode);
	}
}


bool PollEngine::isAlive()
{
	return false;
}

void PollEngine::closeConnection()
{
}


std::vector<Request>* PollEngine::initializeRequests()
{
	return nullptr;
}

void * PollEngine::run()
{
	int iResult = this->makeConnection(this->sock, nullptr, this->ipAddress, this->port, this->nonBlockingMode);

	this->sendRequests(this->sock, this->requests, this->response, this->myBuffer, this->closeConn, this->nonBlockingMode);

	return reinterpret_cast<void*>(threadId);
}

void PollEngine::receiveResponse(SOCKET *connectSocket, char *request, char * response, Buffer * buffer, bool closeConnection, unsigned long int nonBlockingMode)
{
	int iResult = 0;
	iResult = tcpdriver->receiveResponse(connectSocket,nullptr, request, response, closeConnection, nonBlockingMode, buffer);
	if (iResult == -1) {
		std::cout << "Desila se greska!" << std::endl;
	}
}

