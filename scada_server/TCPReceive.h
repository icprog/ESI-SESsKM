#pragma once
#ifndef  TCP_RECEIVE_H
#define TCP_RECEIVE_H
#include "TCPState.h"
#include "TCPActive.h"
#include "TCPClose.h"
#include "SocketNB.h"
class TCPReceive : public TCPState {
public:
	static TCPState* Instance();
	virtual void receive(TCPConnection *t, SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b);
};

#endif