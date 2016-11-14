#pragma once
#ifndef  CLIENT_HANDLER_H
#define CLIENT_HANDLER
#include "IComponent.h"
#include "IServerMediator.h"
#include "TCPDriver.h"
#include "Thread.h"
#include "Buffer.h"
#include <vector>
#define DEFAULT_BUFLEN 512
class ClientHandler : public IComponent, public Thread {
protected:
	IServerMediator *serverMediator;
	int threadId;
	char commBuffer[DEFAULT_BUFLEN];
	unsigned long int nonBlockingMode;
	bool closeConn;
	char* ipAddress;
	int port;
	SOCKET *acceptedSocket;
	SOCKET *listenSocket;
public:
	ClientHandler(int threadId_, unsigned long int nonBlockingMode_, bool closeConn, char *ipAddress_, int port_, SOCKET *acceptedSocket_, SOCKET *listenSocket_)
		: threadId(threadId_), nonBlockingMode(nonBlockingMode_), closeConn(closeConn), ipAddress(ipAddress_), port(port_), acceptedSocket(acceptedSocket_), listenSocket(listenSocket_)
	{
		tcpdriver = new TCPDriver();
	}
	ClientHandler() { tcpdriver = new TCPDriver(); }
	void notifyMediator();
	int makeConnection(SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, unsigned long int nonBlockingMode);
	bool isAlive();
	void closeConnection();
	void sendRequests(SOCKET *connectSocket, std::vector<Request*> *requests, char * response, Buffer * buffer, bool closeConnection, unsigned long int nonBlockingMode);

	std::vector<Request> *initializeRequests();
	virtual void* run();
	
	virtual ~ClientHandler() {
		delete tcpdriver, tcpdriver = 0;
	}
private:
	TCPDriver *tcpdriver;
	void receiveResponse(SOCKET *connectSocket, char *request, char *response, Buffer *buffer, bool closeConnection, unsigned long int nonBlockingMode);
	char buffer[DEFAULT_BUFLEN];
};

#endif // ! ICOMPONENT_MEDIATOR_H