#include "stdafx.h"
#include "ClientHandler.h"

void ClientHandler::notifyMediator()
{
}

int ClientHandler::makeConnection(SOCKET * connectSocket, SOCKET * listenSocket, char * ipAddress, int port, unsigned long int nonBlockingMode)
{
	return tcpdriver->connectt(connectSocket, listenSocket, ipAddress, port, nonBlockingMode);
}

void * ClientHandler::run()
{
	int iResult = this->makeConnection(this->acceptedSocket, this->listenSocket, this->ipAddress, this->port, this->nonBlockingMode);

	return reinterpret_cast<void*>(threadId);
}
