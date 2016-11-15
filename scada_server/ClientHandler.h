#pragma once
#ifndef  CLIENT_HANDLER_H
#define CLIENT_HANDLER_H
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
	char receiveBuffer[DEFAULT_BUFLEN];
	char sendBuffer[DEFAULT_BUFLEN];
	unsigned long int nonBlockingMode;
	bool closeConn;
	char* ipAddress;
	int port;
	SOCKET *listenSocket;
	SOCKET *acceptSocket;
public:
	ClientHandler(int threadId_,unsigned long int nonBlockingMode_, bool closeConnection_, char *ipAddress_, int port_, SOCKET *listenSocket_, SOCKET *acceptSocket_)
		: threadId(threadId_), nonBlockingMode(nonBlockingMode_), closeConn(closeConnection_), ipAddress(ipAddress_), port(port_), listenSocket(listenSocket_), acceptSocket(acceptSocket_)
	{
		tcpdriver = new TCPDriver();
	}
	ClientHandler() { tcpdriver = new TCPDriver(); }
	void notifyMediator();
	int makeConnection(SOCKET *listenSocket, SOCKET *acceptSocket, char* ipAddress, int port, unsigned long int nonBlockingMode);
	bool isAlive();
	void closeConnection();
	void sendRequests(SOCKET *connectSocket, std::vector<Request*> *requests, char * response, Buffer * buffer, bool closeConnection, unsigned long int nonBlockingMode);

	virtual void* run();
	
	virtual ~ClientHandler() {
	delete tcpdriver, tcpdriver = 0;
	}
private:
	TCPDriver *tcpdriver;
	void receiveResponse(SOCKET *acceptSocket, char *request, bool closeConnection, unsigned long int nonBlockingMode);
	char buffer[DEFAULT_BUFLEN];
};

#endif // ! ICOMPONENT_MEDIATOR_H