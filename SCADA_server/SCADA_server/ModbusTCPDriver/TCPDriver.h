#pragma once
#ifndef  TCP_DRIVER_H
#define TCP_DRIVER_H
#include "stdafx.h"

class TCPDriver {
public:
	~TCPDriver() {}

	char *createRequest(char functionCode, char *startingAddress, char *quantityOfCoils);
	int sendRequest(char *request);
	int receiveResponse();
	int pushInBuffer();
	int tpcpConnect();
	int tcpCloseConnection();
	static TCPDriver& getInstance()
	{
		static TCPDriver instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}
	TCPDriver(TCPDriver const&) = delete;
	void operator=(TCPDriver const&) = delete;
	SOCKET *getSocket() const;
	void setSocket(SOCKET *socket);
	char *getIpAddress() const;
	void setIpAddress(char *ipAddress);
	int getPort() const;
	void setPort(int port);
private:
	TCPDriver() {
		socket = INVALID_SOCKET;
	}
	SOCKET socket;
	//Buffer *sharedBuffer;
	//char *response;
	char *ipAddress;
	int port;
};


#endif // ! TCP_DRIVER_H