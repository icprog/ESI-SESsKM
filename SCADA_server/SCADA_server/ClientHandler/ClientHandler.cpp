#include "stdafx.h"
#include "ClientHandler.h"

int ClientHandler::tcpCloseConnection()
{
	for (int i = 0; i < acceptSocketArray->getSize(); i++) {
		closesocket(acceptSocketArray->getValue(i));
	}
	closesocket(listenSocket);
	return 0;
}
