#pragma once
#ifndef  POLL_ENGINE_H
#define POLL_ENGINE_H
#include "IComponent.h"
#include "IServerMediator.h"
#include "TCPDriver.h"
#include "Thread.h"
#include "Buffer.h"
#include <vector>
#define DEFAULT_BUFLEN 512
class PollEngine : public IComponent, public Thread {
protected:
	IServerMediator *serverMediator;
	int threadId;
	Buffer *myBuffer;
	std::vector<Request*> *requests;
	char response[DEFAULT_BUFLEN];
	unsigned long int nonBlockingMode;
	bool closeConn;
	char* ipAddress;
	int port;
	SOCKET *sock;
public:
	PollEngine( int threadId_, Buffer *buffer_, std::vector<Request*> *requests_, unsigned long int nonBlockingMode_, bool closeConnection_, char *ipAddress_, int port_, SOCKET *sock_)
		:  threadId(threadId_), myBuffer(buffer_), requests(requests_), nonBlockingMode(nonBlockingMode_), closeConn(closeConnection_), ipAddress(ipAddress_), port(port_), sock(sock_)
	{ tcpdriver = new TCPDriver(); }
	PollEngine(){ tcpdriver = new TCPDriver();}
	void notifyMediator(); 
	int makeConnection(SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, unsigned long int nonBlockingMode);
	bool isAlive();
	void closeConnection();
	void sendRequests(SOCKET *connectSocket, std::vector<Request*> *requests, char * response, Buffer * buffer, bool closeConnection, unsigned long int nonBlockingMode);

	std::vector<Request> *initializeRequests();
	virtual void* run();
	/*
	virtual ~PollEngine() {
		delete tcpdriver, tcpdriver = 0;
	}*/
private:
	TCPDriver *tcpdriver;
	void receiveResponse(SOCKET *connectSocket, char *request, char *response, Buffer *buffer, bool closeConnection, unsigned long int nonBlockingMode);
	char buffer[DEFAULT_BUFLEN];
};

#endif // ! ICOMPONENT_MEDIATOR_H