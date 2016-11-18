#include "stdafx.h"
#ifndef  TCP_DRIVER_H
#define TCP_DRIVER_H

class TCPDriver {

public:
	TCPDriver() {}
	~TCPDriver() {}
	/*
		This function is used for creating request. It makes tcpHeader internally and glue it to the rest of the the message,
		making complete modbus-tcp request.
		@param functionCode - 1 byte
		@param startingAddress - 2 bytes
		@param quantityOfCoils - 2 bytes
		@return request - 12 bytes
	*/
	char * createRequest(char functionCode, char *startingAddress, char *quantityOfCoils);
	/*
		This function is used for sending request over tcp connection.
		@param request - 12 bytes got from createRequest function. Example call: sendRequest(createRequest(...))
		@return enum value
	*/

	int sendRequest(char *request);
	/*
	*/

	int pushInBufer()

};

#endif // ! TCP_DRIVER_H
