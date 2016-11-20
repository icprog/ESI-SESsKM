#pragma once
#ifndef  CLIENT_HANDLER_H
#define CLIENT_HANDLER_H
#include "stdafx.h"
#define DEFAULT_POOL_SIZE 10
class ClientHandler {
public:
	ClientHandler() {
		acceptSocketArray = new std::vector<SOCKET>();
		SOCKET s = INVALID_SOCKET;
		for (int i = 0; i < DEFAULT_POOL_SIZE; i++) {
			acceptSocketArray->push_back(s);
		}
		threadArray = new std::vector<std::thread*>();
		
		for (int i = 0; i < DEFAULT_POOL_SIZE; i++) {
			threadArray->push_back(new std::thread());
			//delete t, t = 0;
		}
		
		threadFinished = new std::vector<bool>();
		for (int i = 0; i < DEFAULT_POOL_SIZE; i++) {
			threadFinished->push_back(true);
		}	

		nonBlockingSocket = new NonBlockingSocket();
	}
	ClientHandler(Buffer *commandingBuffer_, Buffer *streamBuffer_, unsigned long nonBlockingMode_, char *ipAddress_, char *port_, RemoteTelemetryUnit *rtu_):
	commandingBuffer(commandingBuffer_), streamBuffer(streamBuffer_), nonBlockingMode(nonBlockingMode_), ipAddress(ipAddress_), port(port_), rtu(rtu_)
	{
		/* INITIALIZE SOCKET AND THREAD ARRAYS */
		acceptSocketArray = new std::vector<SOCKET>();
		SOCKET s = INVALID_SOCKET;
		for (int i = 0; i < DEFAULT_POOL_SIZE; i++) {
			acceptSocketArray->push_back(s);
		}
		threadArray = new std::vector<std::thread*>();
		std::thread *t = new std::thread();
		for (int i = 0; i < DEFAULT_POOL_SIZE; i++) {
			threadArray->push_back(new std::thread());
		}
		delete t, t = 0;
		threadFinished = new std::vector<bool>();
		for (int i = 0; i < DEFAULT_POOL_SIZE; i++) {
			threadFinished->push_back(true);
		}
		nonBlockingSocket = new NonBlockingSocket();
	}
	~ClientHandler() {
		delete ipAddress, ipAddress = 0;
		delete port, port = 0;
		delete nonBlockingSocket, nonBlockingSocket = 0;
		delete acceptSocketArray, acceptSocketArray = 0;
		delete threadArray, threadArray = 0;
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

	static int sendMessage(SOCKET *accSock,ClientHandler*tmp);  // if stream buffer is not empty it pops from it and sends to client
	void sendData(char * message, SOCKET * accSock);
	static void receiveMessage(SOCKET *accSock, ClientHandler*tmp);
	void pushCommand();
	char *popFromStreamBuffer();
	NonBlockingSocket *getNonBlockingSocket();
	RemoteTelemetryUnit *getRTU() { return rtu; }
	Buffer *getCommandingBuffer() { return commandingBuffer; }
private:
	//SOCKET acceptSocket;
	SOCKET listenSocket;
	char *ipAddress;
	char *port;
	unsigned long int nonBlockingMode;
	std::vector<SOCKET> *acceptSocketArray;
	std::vector<std::thread*> *threadArray;
	std::vector<bool> *threadFinished;
	Buffer *commandingBuffer;
	Buffer *streamBuffer;
	NonBlockingSocket *nonBlockingSocket;
	int listenSocketFunc(SOCKET * listenSocket, char * port);
	int selectt(SOCKET * socket, int type, int * exit);
	int acceptt(SOCKET * acceptedSocket, SOCKET * listenSocket);
	RemoteTelemetryUnit *rtu;
};

#endif // ! CLIENT_HANDLER_H