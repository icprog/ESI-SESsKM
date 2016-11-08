#pragma once
#ifndef  TCP_CONNECT_H
#define TCP_CONNECT_H
#include "TCPState.h"
#include "TCPSend.h"
#include "SocketNB.h"
#include <iostream>
#include <ws2tcpip.h>

class TCPConnect : public TCPState {
public:
	static TCPState* Instance();/* char *request, bool closeSocket, char *responseBuffer*/
	virtual void connectt(TCPConnection *t, SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b);
private:
	int createSocket(TCPConnection *t, SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b);
	int listenSocketFunc(SOCKET * listenSocket, char * port);
	int selectt(SOCKET * socket, int type, int *exit);
	int acceptt(SOCKET * acceptedSocket, SOCKET* listenSocket);

};

#endif