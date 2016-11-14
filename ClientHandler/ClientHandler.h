#pragma once
#ifndef  CLIENT_HANDLER_H
#define CLIENT_HANDLER
#include "../Mediator/IComponent.h"
#include "../Mediator/IServerMediator.h"
#include "../TCPDriver/TCPDriver.h"
#include "../Thread/Thread.h"
#include "../DataStructures/Buffer.h"
#include <vector>
#define DEFAULT_BUFLEN 512
enum request { SEND_ME_ALL = 1 };
class ClientHandler : public IComponent, public Thread {
protected:
	IServerMediator *serverMediator;
	int threadId;
	char commBuffer[DEFAULT_BUFLEN];
	unsigned long int nonBlockingMode;
	bool closeConn;
	char* ipAddress;
	int port;
	char request[512];
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
	void sendResponse(SOCKET *connectSocket, char *request);
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