#pragma once
#ifndef  TCP_SEND_H
#define TCP_SEND_H
#include "TCPState.h"
#include "TCPClose.h"
#include "TCPReceive.h"
#include "TCPActive.h"
class TCPSend : public TCPState {
public:
	static TCPState* Instance();
	virtual void send(TCPConnection *t, SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode);
private:
	int createSocket(SOCKET *, char *, int);
	int sendMessage(SOCKET * socket, char * data);
};

#endif