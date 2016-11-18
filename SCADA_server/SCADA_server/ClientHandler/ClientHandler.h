#pragma once
#ifndef  CLIENT_HANDLER_H
#define CLIENT_HANDLER_H
#include "stdafx.h"

class ClientHandler {
public:
	ClientHandler() {
		acceptSocketArray = new Pool<SOCKET>(INVALID_SOCKET);
		nonBlockingSocket = new NonBlockingSocket();
	}
	ClientHandler(Buffer *commandingBuffer_, Buffer *streamBuffer_, unsigned long nonBlockingMode_, char *ipAddress_, char *port_):
	commandingBuffer(commandingBuffer_), streamBuffer(streamBuffer_), nonBlockingMode(nonBlockingMode_), ipAddress(ipAddress_), port(port_)
	{
		acceptSocketArray = new Pool<SOCKET>(INVALID_SOCKET);
		nonBlockingSocket = new NonBlockingSocket();
	}
	~ClientHandler() {
		delete ipAddress, ipAddress = 0;
		delete port, port = 0;
		delete nonBlockingSocket, nonBlockingSocket = 0;
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

	int sendMessage(char *message, SOCKET *accSock);  // if stream buffer is not empty it pops from it and sends to client
	void sendData(char * message, SOCKET * accSock);
	char * receiveMessage(SOCKET *accSock);
	void pushCommand();
	char *popFromStreamBuffer();
private:
	//SOCKET acceptSocket;
	SOCKET listenSocket;
	char *ipAddress;
	char *port;
	unsigned long int nonBlockingMode;
	Pool<SOCKET> *acceptSocketArray;
	Buffer *commandingBuffer;
	Buffer *streamBuffer;
	NonBlockingSocket *nonBlockingSocket;
	int listenSocketFunc(SOCKET * listenSocket, char * port);
	int selectt(SOCKET * socket, int type, int * exit);
	int acceptt(SOCKET * acceptedSocket, SOCKET * listenSocket);

};

#endif // ! CLIENT_HANDLER_H