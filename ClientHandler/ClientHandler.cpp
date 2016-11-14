#include "stdafx.h"
#include "ClientHandler.h"

void ClientHandler::notifyMediator()
{
}

int ClientHandler::makeConnection(SOCKET * connectSocket, SOCKET * listenSocket, char * ipAddress, int port, unsigned long int nonBlockingMode)
{
	return tcpdriver->connectt(connectSocket, listenSocket, ipAddress, port, nonBlockingMode);
}

void ClientHandler::sendResponse(SOCKET * connectSocket, char * request)
{
	tcpdriver->receiveResponse(connectSocket, nullptr, request, commBuffer, false, 1, nullptr);

}

void * ClientHandler::run()
{
	int iResult = this->makeConnection(this->acceptedSocket, this->listenSocket, this->ipAddress, this->port, this->nonBlockingMode);
	sendResponse(this->acceptedSocket, this->request);
	return reinterpret_cast<void*>(threadId);
}
