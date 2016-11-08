#pragma once
#ifndef  TCP_CLOSE_H
#define TCP_CLOSE_H
#include "TCPState.h"
#include "TCPConnect.h"
class TCPClose : public TCPState {
public:
	static TCPState* Instance();
	virtual void close(TCPConnection *t, SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b);
};

#endif