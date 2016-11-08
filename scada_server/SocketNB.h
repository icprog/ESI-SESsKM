#pragma once
#ifndef  SOCKET_NB_H
#define SOCKET_NB_H
#include <WinSock2.h>

class SocketNB {
public:
	int SEND(SOCKET* socket, char* buffer);
	int RECEIVE(SOCKET* socket, char* buffer);
	int getMessageLength(char *buffer);
private:
	int sendNB(SOCKET* socket, char* buffer, int bufferLength);
	int receiveNB(SOCKET* socket, char* buffer, int bufferLength, int continueFrom);
};

#endif