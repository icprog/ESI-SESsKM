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
	ClientHandler(BlockingQueue<char *> *commandingBuffer_, BlockingQueue<char *> *streamBuffer_, BlockingQueue<char *> *alarmBuffer_, unsigned long nonBlockingMode_, char *ipAddress_, char *port_, RemoteTelemetryUnit *rtu_) :
		commandingBuffer(commandingBuffer_), streamBuffer(streamBuffer_),alarmBuffer(alarmBuffer_), nonBlockingMode(nonBlockingMode_), ipAddress(ipAddress_), port(port_), rtu(rtu_)
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

	static int sendMessage(SOCKET *accSock, ClientHandler*tmp);  // if stream buffer is not empty it pops from it and sends to client
	static void sendAlarm(SOCKET *accSock, ClientHandler*tmp);
	static void receiveMessage(SOCKET *accSock, ClientHandler*tmp);
	void pushCommand();
	char *popFromStreamBuffer();
	char * popFromAlarmBuffer();
	NonBlockingSocket *getNonBlockingSocket();
	RemoteTelemetryUnit *getRTU() { return rtu; }
	BlockingQueue<char *> *getCommandingBuffer() { return commandingBuffer; }
	int listenSocketFunc(SOCKET * listenSocket, char * port);
	int selectt(SOCKET * socket, int type, int * exit);
	int acceptt(SOCKET * acceptedSocket, SOCKET * listenSocket);
	SOCKET *getListenSocket() { return &listenSocket; }
	char *getPort() { return port; }
	char *getIpAddress() { return ipAddress; }
	unsigned long int getNonBlockingMode() { return nonBlockingMode; }
	void pushinIntegrityBuffer(ClientHandler*tmp, SOCKET *accSock);
private:
	//SOCKET acceptSocket;
	SOCKET listenSocket;
	char *ipAddress;
	char *port;
	unsigned long int nonBlockingMode;
	std::vector<SOCKET> *acceptSocketArray;
	std::vector<std::thread*> *threadArray;
	std::vector<bool> *threadFinished;
	BlockingQueue<char *> *commandingBuffer;
	BlockingQueue<char *> *streamBuffer;
	BlockingQueue<char *> *alarmBuffer;
	
	NonBlockingSocket *nonBlockingSocket;

	RemoteTelemetryUnit *rtu;
};

#endif // ! CLIENT_HANDLER_H