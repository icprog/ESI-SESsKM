#include "stdafx.h"
#include "ClientHandler.h"

void ClientHandler::notifyMediator()
{
}

int ClientHandler::makeConnection(SOCKET * listenSocket, SOCKET * acceptSocket, char * ipAddress, int port, unsigned long int nonBlockingMode)
{
	return tcpdriver->connectt(acceptSocket, listenSocket, ipAddress, port, nonBlockingMode);
}

void * ClientHandler::run()
{
	int iResult = makeConnection(this->listenSocket, this->acceptSocket, this->ipAddress, this->port, this->nonBlockingMode);
	if (iResult == 0)
		receiveResponse(this->acceptSocket, nullptr, this->closeConn, this->nonBlockingMode);
	return reinterpret_cast<void*>(threadId);
}

void ClientHandler::receiveResponse(SOCKET * acceptSocket, char * request, bool closeConnection, unsigned long int nonBlockingMode)
{
	tcpdriver->receiveResponse(acceptSocket, request, this->receiveBuffer, closeConn, nonBlockingMode, nullptr);
}

