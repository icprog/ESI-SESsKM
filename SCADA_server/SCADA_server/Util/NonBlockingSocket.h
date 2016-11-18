#pragma once
#ifndef  NON_BLOCKING_SOCKET_H
#define NON_BLOCKING_SOCKET_H
#include "stdafx.h"
class NonBlockingSocket {
public:
	int SEND(SOCKET* socket, char* buffer, int type);
	int RECEIVE(SOCKET* socket, char* buffer, int type);
	int getMessageLength(char *buffer);
private:
	int sendNB(SOCKET* socket, char* buffer, int bufferLength);
	int receiveNB(SOCKET* socket, char* buffer, int bufferLength, int continueFrom);
};
#endif // ! NON_BLOCKING_SOCKET_H