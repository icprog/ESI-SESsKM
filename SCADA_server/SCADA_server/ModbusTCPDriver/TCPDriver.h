#pragma once
#ifndef  TCP_DRIVER_H
#define TCP_DRIVER_H
#include "stdafx.h"

class TCPDriver {
public:

	/*
	This function is used for creating request. It makes tcpHeader internally and glue it to the rest of the the message,
	making complete modbus-tcp request.

	@param req - 1 byte function code, 2 bytes starting address, 2 bytes quantity of coils
	@return request - 12 bytes
	*/
	void createRequest(char *req, char *whole_req);
	/*
	This function is used for sending request over tcp connection.

	@param request - 12 bytes got from createRequest function. Example call: sendRequest(createRequest(...))
	@return enum value
	*/
	int sendRequest(char *request);
	/*
	This function is used for receiving response from the modbus simulator.
	It makes message that has this format:
	4 bytes for the length of the whole message +
	4 bytes for the length of the response +
	n bytes for the response +
	12 bytes for the request
	@param request is request that produces the given response.

	*/
	int receiveResponse(char *request);
	/*
	Connection is made with the modbus simulator. Supporting functions are private.
	*/
	int tcpConnect();
	/*
	In this function connection is closing. Socket is destroying.
	*/
	int tcpCloseConnection();
	/*
	TCPDriver is organized as a singleton. There is only one instance of this class.
	*/
	static TCPDriver& getInstance()
	{
		static TCPDriver instance; // Guaranteed to be destroyed.
								   // Instantiated on first use.
		return instance;
	}
	/*
	We need to delete copy constructor and assignment operator in order to forbid their use, because of the singleton pattern logic.
	*/
	TCPDriver(TCPDriver const&) = delete;
	void operator=(TCPDriver const&) = delete;

	SOCKET *getSocket();
	void setSocket(SOCKET *socket);
	char *getIpAddress() const;
	void setIpAddress(char *ipAddress);
	int getPort() const;
	void setPort(int port);
	void setSharedBuffer(BlockingQueue<char *> *buffer) { sharedBuffer = buffer; }
	BlockingQueue<char *> *getSharedBuffer();
private:
	TCPDriver() {
		nonBlockingSocket = new NonBlockingSocket();
		sock = INVALID_SOCKET;
		//tcpConnect();
	}
	TCPDriver(char *ipAddress_, int port_, BlockingQueue<char *> *sharedBuffer_, unsigned long int nonBlockingMode_) :
		ipAddress(ipAddress_), port(port_), nonBlockingMode(nonBlockingMode_), sharedBuffer(sharedBuffer_) {
		nonBlockingSocket = new NonBlockingSocket();
		sock = INVALID_SOCKET;
		//tcpConnect();
	}
	~TCPDriver() {
		delete ipAddress, ipAddress = 0;
		delete nonBlockingSocket, nonBlockingSocket = 0;
		tcpCloseConnection();
	}
	SOCKET sock;
	BlockingQueue<char *> *sharedBuffer;
	//char *response;
	char *ipAddress;
	int port;
	unsigned long int nonBlockingMode;
	NonBlockingSocket *nonBlockingSocket;
	/*
	Supporting function. It is used inside tcpConnect() and its job is to create and open socket towards modbus simulator.
	*/
	int createSocket();
	int selectt(int type);

};


#endif // ! TCP_DRIVER_H