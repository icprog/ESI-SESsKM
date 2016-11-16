#pragma once
#ifndef  CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include "TCPDriver.h"
#include "Thread.h"
#include "Buffer.h"
#include <vector>
#include "SocketNB.h"


#define DEFAULT_BUFLEN 512
class ClientHandler : public Thread {
protected:

	int threadId;
	char receiveBuffer[DEFAULT_BUFLEN];
	char sendBuffer[DEFAULT_BUFLEN];
	unsigned long int nonBlockingMode;
	bool closeConn;
	char* ipAddress;
	int port;
	SOCKET *listenSocket;
	SOCKET *acceptSocket;
	Buffer *myBuffer;
public:
	ClientHandler(int threadId_, unsigned long int nonBlockingMode_, bool closeConnection_, char *ipAddress_, int port_, SOCKET *listenSocket_, SOCKET *acceptSocket_, Buffer *myBuffer_)
		: threadId(threadId_), nonBlockingMode(nonBlockingMode_), closeConn(closeConnection_), ipAddress(ipAddress_), port(port_), listenSocket(listenSocket_), acceptSocket(acceptSocket_), myBuffer(myBuffer_)
	{
		socketNb = new SocketNB();
		//std::unique_ptr<ClientHandlerReceive> chr(new ClientHandlerReceive(1, buffer, &vec, 1, false, "127.0.0.1", 502, &sock));
		//chr->start();
		//int result1 = reinterpret_cast<int>(chr->join());
	}
	ClientHandler() {  
		socketNb = new SocketNB();
		//std::unique_ptr<ClientHandlerReceive> chr(new ClientHandlerReceive(1, buffer, &vec, 1, false, "127.0.0.1", 502, &sock));
		//chr->start();
		//int result1 = reinterpret_cast<int>(chr->join());
	
	}
	int makeConnection(SOCKET *listenSocket, SOCKET *acceptSocket, char* ipAddress, int port, unsigned long int nonBlockingMode);
	int createSocket(SOCKET * connectSocket, SOCKET * listenSocket, char * ipAddress, int port, unsigned long int nonBlockingMode);
	int listenSocketFunc(SOCKET * listenSocket, char * port);
	int selectt(SOCKET * socket, int type, int * exit);
	int acceptt(SOCKET * acceptedSocket, SOCKET * listenSocket);
	int sendMessage(SOCKET * socket, char * data);
	void closeConnection();
	void sendToClient(SOCKET *acceptSocket,  char * message, Buffer *buffer, bool closeConnection, unsigned long int nonBlockingMode);
	void receiveFromClient(SOCKET *acceptSocket, char * message, Buffer *buffer, bool closeConnection, unsigned long int nonBlockingMode);

	virtual void* run();

	virtual ~ClientHandler() {
		delete socketNb, socketNb = 0;
	}
private:
	SocketNB *socketNb;
	void receiveResponse(SOCKET *acceptSocket, char *request, bool closeConnection, unsigned long int nonBlockingMode);
	void parseResponse(char *response);
	char buffer[DEFAULT_BUFLEN];
};

#endif // ! ICOMPONENT_MEDIATOR_H