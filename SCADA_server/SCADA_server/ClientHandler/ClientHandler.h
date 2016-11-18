#pragma once
#ifndef  CLIENT_HANDLER_H
#define CLIENT_HANDLER_H
#include "stdafx.h"

class ClientHandler {
public:
	ClientHandler() {
		acceptSocketArray = new Pool<SOCKET>(INVALID_SOCKET);
	}
	~ClientHandler() {
		delete ipAddress, ipAddress = 0;
		delete port, port = 0;
		//delete acceptSocketArray, acceptSocketArray = 0;
		tcpCloseConnection();
	}
	/*
		Connection is made with clients. There are supporting private functions.
	*/
	int tcpConnect();
	/*
		Close all sockets.
	*/
	int tcpCloseConnection();
	int sendMessage(char *message);  // if stream buffer is not empty it pops from it and sends to client
	int receiveMessage();
	void pushCommand();
private:
	//SOCKET acceptSocket;
	SOCKET listenSocket;
	char *ipAddress;
	char *port;
	Pool<SOCKET> *acceptSocketArray;
	// Buffer *commandingBuffer;
	// Buffer *streamBuffer;

};

#endif // ! CLIENT_HANDLER_H