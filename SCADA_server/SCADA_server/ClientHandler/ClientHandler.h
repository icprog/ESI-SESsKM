#pragma once
#ifndef  CLIENT_HANDLER_H
#define CLIENT_HANDLER_H
#include "stdafx.h"

class ClientHandler {
public:
	ClientHandler() {}
	~ClientHandler() {}

	int tcpConnect();
	int tcpCloseConnection();
	int sendMessage(char *message);  // if stream buffer is not empty it pops from it and sends to client
	int receiveMessage();
	void pushCommand();
private:
	SOCKET acceptSocket;
	SOCKET listenSocket;
	char *ipAddress;
	char *port;
	// Buffer *commandingBuffer;
	// Buffer *streamBuffer;

};

#endif // ! CLIENT_HANDLER_H