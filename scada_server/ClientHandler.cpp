#include "stdafx.h"
#include "ClientHandler.h"

int ClientHandler::makeConnection(SOCKET * listenSocket, SOCKET * acceptSocket, char * ipAddress, int port, unsigned long int nonBlockingMode)
{
	int iResult = -1;
	iResult = createSocket(acceptSocket, listenSocket, ipAddress, port, nonBlockingMode);
	std::cout << "\nLISTEN SOCKET IZ SERVERA: %d\n" << *acceptSocket << std::endl;

	if (iResult != 0) {
		//WSACleanup();

		// ERROR
	}
	return iResult;
	return 0;
}
int ClientHandler::createSocket(SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, unsigned long int nonBlockingMode)
{

		char cport[16];
		_itoa(port, cport, 10);
		int iResult = -1;
		iResult = listenSocketFunc(listenSocket, cport);
		if (iResult == 1) {
			// Ako je ovde greska, kraj rada
			return 1;
		}

			iResult = ioctlsocket(*connectSocket, FIONBIO, &nonBlockingMode);
			selectt(listenSocket, 0, 0);
			// Wait for clients and accept client connections.
			// Returning value is acceptedSocket used for further
			// Client<->Server communication. This version of
			// server will handle only one client.
			iResult = acceptt(connectSocket, listenSocket);
			if (iResult == 1) {
				// Ako je ovde greska, kraj rada
				return 1;
			}
		



	return 0;
}



int ClientHandler::listenSocketFunc(SOCKET * listenSocket, char * port)
{

	// variable used to store function return value
	int iResult;

	// Prepare address information structures
	addrinfo *resultingAddress = NULL;
	addrinfo hints;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;       // IPv4 address
	hints.ai_socktype = SOCK_STREAM; // Provide reliable data streaming
	hints.ai_protocol = IPPROTO_TCP; // Use TCP protocol
	hints.ai_flags = AI_PASSIVE;     // 

									 // Resolve the server address and port
	iResult = getaddrinfo(NULL, port, &hints, &resultingAddress);
	if (iResult != 0)
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	*listenSocket = socket(AF_INET,      // IPv4 address famly
		SOCK_STREAM,  // stream socket
		IPPROTO_TCP); // TCP

	if (*listenSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(resultingAddress);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket - bind port number and local address 
	// to socket
	iResult = bind(*listenSocket, resultingAddress->ai_addr, (int)resultingAddress->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(resultingAddress);
		closesocket(*listenSocket);
		WSACleanup();
		return 1;
	}

	// Since we don't need resultingAddress any more, free it
	freeaddrinfo(resultingAddress);

	unsigned long int nonBlockingMode = 1;
	iResult = ioctlsocket(*listenSocket, FIONBIO, &nonBlockingMode);

	// Set listenSocket in listening mode
	iResult = listen(*listenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(*listenSocket);
		WSACleanup();
		return 1;
	}

	printf("Server initialized, waiting for clients.\n");

	return iResult;
}

int ClientHandler::selectt(SOCKET * socket, int type, int *exit)
{
	FD_SET set;
	timeval timeVal;
	int iResult;

	do {
		iResult = 0;
		FD_ZERO(&set);
		// Add socket we will wait to read from
		FD_SET(*socket, &set);

		// Set timeouts to zero since we want select to return
		// instantaneously
		timeVal.tv_sec = 0;
		timeVal.tv_usec = 0;
		if (type == 0)  //receive
		{
			iResult = select(0 /* ignored */, &set, NULL, NULL, &timeVal);
		}
		else {
			iResult = select(0 /* ignored */, NULL, &set, NULL, &timeVal);
		}
		// lets check if there was an error during select
		if (iResult == SOCKET_ERROR)
		{
			fprintf(stderr, "select failed with error: %ld\n", WSAGetLastError());
			return -1; //error code: -1
		}

		// now, lets check if there are any sockets ready
		if (iResult == 0)
		{
			//printf("\n SPAVAM! ");
			// there are no ready sockets, sleep for a while and check again
			Sleep(200);
		}

	} while (iResult == 0);

	return iResult;
}

int ClientHandler::acceptt(SOCKET * acceptedSocket, SOCKET* listenSocket)
{
	*acceptedSocket = accept(*listenSocket, 0, 0);

	if (*acceptedSocket == INVALID_SOCKET)
	{
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(*listenSocket);
		WSACleanup();
		return 1;
	}
	return 0;
}

int ClientHandler::sendMessage(SOCKET * socket, char * data)
{
	int iResult = -1;
	// Send an prepared message with null terminator included

	printf("\nSENDING MESSAGE: %s", data);

	iResult = socketNb->SEND(socket, data, 1);

	if (iResult == SOCKET_ERROR)
	{
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(*socket);
		//WSACleanup();
		return 1;
	}

	printf("\nMESSAGE SENT! Bytes Sent: %ld\n", iResult);
	return 0;
}

void ClientHandler::closeConnection()
{
}

void ClientHandler::sendToClient(SOCKET * acceptSocket, char * message, Buffer *buffer, bool closeConnection, unsigned long int nonBlockingMode)
{
	if (buffer->getPopIdx() != buffer->getPushIdx()) {
		buffer->pop(message, 1);
		sendMessage(acceptSocket, message);
		receiveFromClient(acceptSocket, message, buffer, closeConnection, nonBlockingMode);
	}
}

void ClientHandler::receiveFromClient(SOCKET * acceptSocket, char * message, Buffer * buffer, bool closeConnection, unsigned long int nonBlockingMode)
{
	int iResult = -1;
	do {
		iResult = socketNb->RECEIVE(acceptSocket, message, 1);
		printf("%d", iResult);
		if (iResult > 0)
		{
			printf("Message received from client: %s.\n", message);
			//// OBRADA PORUKE OD STRANE KLIJENTA
			parseResponse(message);


			iResult = 0;
		}
		if (iResult == 0)
		{
			// connection was closed gracefully
			printf("Connection with server established.\n");
			//closesocket(*acceptedSocket);
			break;
		}
		else
		{
			// there was an error during recv
			printf("recv failed with error: %d\n", WSAGetLastError());
			//closesocket(*acceptedSocket);
			break;
		}

	} while (iResult > 0);


}

void * ClientHandler::run()
{
	int iResult = this->makeConnection(this->listenSocket, this->acceptSocket, this->ipAddress, this->port, this->nonBlockingMode);
	while (1) {
		this->sendToClient(this->acceptSocket, this->sendBuffer,this->myBuffer, this->closeConn, this->nonBlockingMode);
	}
	return reinterpret_cast<void*>(threadId);
}

void ClientHandler::parseResponse(char * response)
{
	int code = *(int *)response;   // ako je kao odgovor poslat kod znaci 
	switch (code) {
	case 1:
		std::cout << "Klijent je dobio nove podatke!" << std::endl;
		break;
	case 2:
		std::cout << "Potvrda alarma" << std::endl;
		break;
	}
}
