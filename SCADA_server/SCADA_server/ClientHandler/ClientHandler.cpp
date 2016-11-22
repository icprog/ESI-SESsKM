#include "stdafx.h"
#include "ClientHandler.h"

int ClientHandler::tcpConnect()
{

	int iResult = listenSocketFunc(&listenSocket, port);
	if (iResult == 1) {
		// Ako je ovde greska, kraj rada
		return 1;
	}
	while (1)
	{
		u_long nb = 1;
		std::cout << "\nLISTEN SOCKET IZ SERVERA: %d\n" << listenSocket << std::endl;
		iResult = ioctlsocket(listenSocket, FIONBIO, &nb);
		selectt(&listenSocket, 0, 0);
		// Wait for clients and accept client connections.
		// Returning value is acceptedSocket used for further
		// Client<->Server communication. This version of
		// server will handle more clients.
		bool full = true;
		for (int i = 0; i < acceptSocketArray->size(); i++) {
			if (acceptSocketArray->at(i) == INVALID_SOCKET) {
				iResult = acceptt(&acceptSocketArray->at(i), &listenSocket);
				if (iResult == 1) {
					// Ako je ovde greska, kraj rada
					return 1;
				}

				/*
				// create new thread for this client
				bool threadFull = true;
				for (int i = 0; i < threadFinished->size(); i++) {
					if (threadFinished->at(i) == true) { // this thread is free, it can be used
						threadArray->at(i)->join();
						threadFull = false;
						break;
					}
				}

				if (threadFull) {
					// ADD NEW THREAD
				}
				*/
				std::thread sendThread(ClientHandler::sendMessage, &acceptSocketArray->at(i), this);
				std::thread receiveThread(ClientHandler::receiveMessage, &acceptSocketArray->at(i), this);
				sendThread.detach();
				receiveThread.detach();
				full = false;
				break;
			}
		}
		
		if (full) {
			SOCKET soc = INVALID_SOCKET;
			acceptSocketArray->push_back(soc);
			closesocket(soc);
		}
	}
	return 0;
}

int ClientHandler::tcpCloseConnection()
{
	for (int i = 0; i < acceptSocketArray->size(); i++) {
		closesocket(acceptSocketArray->at(i));
	}
	closesocket(listenSocket);
	return 0;
}

 int ClientHandler::sendMessage( SOCKET *accSock, ClientHandler*tmp) // thread function
{
	 while (1) {

		 char *req = tmp->popFromStreamBuffer();
		 if (req == nullptr){ // buffer is empty
			 Sleep(200);
			 continue;
		}
		int iResult = -1;
		// Send an prepared message with null terminator included

		std::cout << "\nSENDING MESSAGE: %s" << req << std::endl;

		iResult = tmp->getNonBlockingSocket()->SEND(accSock, req, 4);

		if (iResult == SOCKET_ERROR)
		{
			std::cout << "send failed with error: %d\n" << WSAGetLastError() << std::endl;
			closesocket(*accSock);
			//WSACleanup();
			return 1;
		}

		std::cout << "\nMESSAGE SENT! Bytes Sent: %ld\n" << iResult << std::endl;
		delete req, req = 0;
		
	}
	return 0;
}

void ClientHandler::receiveMessage(SOCKET *accSock, ClientHandler*tmp)
{
	int iResult = -1;
	char *response = nullptr;
	do {
		response = new char[8012];
		iResult = tmp->nonBlockingSocket->RECEIVE(accSock, response, 4);
		std::cout << iResult << std::endl;
		if (iResult > 0)
		{
			std::cout << "Message received from server as a server: %s.\n" << response << std::endl;

			// if there is alarm in the stream, then the response should look like this: 
			// 4 bytes for size and 2 bytes for the alarm address
			int size = *(int *)response;
			if (size == 6) {
				
				for (int i = 0; i < tmp->getRTU()->getAlarms()->size(); i++) {
					if (tmp->getRTU()->getAlarms()->at(i).getAddress() == *(short*)(response + 4)) {
						tmp->getRTU()->getAlarms()->at(i).setConfirmed(true);
						break;
					}
				}

			}
			else {
				// if it is a command, put it into the command buffer! 
				char *data = new char[size];
				for (int i = 0; i < size; i++) {
					data[i] = response[i];
				}
				tmp->getCommandingBuffer()->push(data, size);
				delete data, data = 0;

			}

			delete response, response = 0;
		}
		else if (iResult == 0)
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
	delete response, response = 0;
}

char * ClientHandler::popFromStreamBuffer()
{
	char *stream = nullptr;
	char size[4];
	while (streamBuffer->getCount()) {
		streamBuffer->pop(size, 4);
		
		int length = *(int *)size;
		stream = new char[length];
		memcpy(stream, size, 4);

		streamBuffer->pop(stream + 4, length - 4);

	}
	return stream;
}

NonBlockingSocket * ClientHandler::getNonBlockingSocket()
{
	return nonBlockingSocket;
}

int ClientHandler::listenSocketFunc(SOCKET * ls, char * port)
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
		std::cout << "getaddrinfo failed with error: %d\n" <<  iResult << std::endl;
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	*ls = socket(AF_INET,      // IPv4 address famly
		SOCK_STREAM,  // stream socket
		IPPROTO_TCP); // TCP

	if (*ls == INVALID_SOCKET)
	{
		std::cout << "socket failed with error: %ld\n" << WSAGetLastError() << std::endl;
		freeaddrinfo(resultingAddress);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket - bind port number and local address 
	// to socket
	iResult = bind(*ls, resultingAddress->ai_addr, (int)resultingAddress->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "bind failed with error: %d\n" << WSAGetLastError() << std::endl;
		freeaddrinfo(resultingAddress);
		closesocket(*ls);
		WSACleanup();
		return 1;
	}

	// Since we don't need resultingAddress any more, free it
	freeaddrinfo(resultingAddress);

	unsigned long int nonBlockingMode = 1;
	iResult = ioctlsocket(*ls, FIONBIO, &nonBlockingMode);

	// Set listenSocket in listening mode
	iResult = listen(*ls, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "listen failed with error: %d\n" <<WSAGetLastError() << std::endl;
		closesocket(*ls);
		WSACleanup();
		return 1;
	}

	std::cout << "Server initialized, waiting for clients.\n" << std::endl;

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
			std::cout << stderr << "select failed with error: %ld\n" << WSAGetLastError() << std::endl;
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
	*acceptedSocket = accept(*listenSocket, NULL, NULL);

	if (*acceptedSocket == INVALID_SOCKET)
	{
		std::cout << "accept failed with error: %d\n" << WSAGetLastError() << std::endl;
		closesocket(*acceptedSocket);
		WSACleanup();
		return 1;
	}
	return 0;
}