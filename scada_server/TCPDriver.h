#pragma once
#ifndef  TCP_DRIVER_H
#define TCP_DRIVER_H
#include "IComponent.h"
#include "IServerMediator.h"
#include "SocketNB.h"
#include "Request.h"
#include <iostream>
#include "Buffer.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
class TCPDriver {
private:
	SocketNB *socketNB;
	int createSocket(SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, unsigned long int nonBlockingMode);
	static int listenSocketFunc(SOCKET * listenSocket, char * port);
	static int selectt(SOCKET * socket, int type);
	static int acceptt(SOCKET * acceptedSocket, SOCKET* listenSocket);
	int sendMessage(SOCKET * socket, char * data);
public:
	TCPDriver() { socketNB = new SocketNB(); }
	~TCPDriver() {
		delete socketNB, socketNB = 0;
	}
	int connectt(SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, unsigned long int nonBlockingMode);
	int sendRequest(SOCKET *sendSocket, char *request, bool closeConnection, unsigned long int nonBlockingMode);
	int receiveResponse(SOCKET *connectSocket, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b);
};

#endif