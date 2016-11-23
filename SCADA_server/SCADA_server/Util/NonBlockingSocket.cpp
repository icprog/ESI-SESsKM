#include "stdafx.h"
#include "NonBlockingSocket.h"

enum codes { SUCCESS = 0, SOCK_ERR = -1, SLEEP = -2, CONN_ERR = -3, SEND_ERR = -4, REC_ERR = -5 };
#define SLEEP_TIME 200

int NonBlockingSocket::sendNB(SOCKET* socket, char* buffer, int bufferLength) {
	int iResult = 0, i = 0;
	int sockAddrLen = sizeof(struct sockaddr);
	FD_SET set;
	timeval timeVal;

	FD_ZERO(&set);
	// Add socket we will wait to read from
	FD_SET(*socket, &set);

	// Set timeouts to zero since we want select to return
	// instantaneously
	timeVal.tv_sec = 0;
	timeVal.tv_usec = 0;

	iResult = select(0 /* ignored */, NULL, &set, NULL, &timeVal);

	// lets check if there was an error during select
	if (iResult == SOCKET_ERROR)
	{
		std::cout << stderr << "select failed with error: %ld\n" << WSAGetLastError() << std::endl;
		return SOCK_ERR; //error code: -1
	}

	// now, lets check if there are any sockets ready
	if (iResult == 0)
	{
		// there are no ready sockets, sleep for a while and check again
		Sleep(SLEEP_TIME);
		return SLEEP; // sleep code: 1
	}


	iResult = send(*socket, buffer, bufferLength, 0);

	if (iResult == SOCKET_ERROR)
	{
		std::cout << "sendto failed with error: %ld\n" << WSAGetLastError() << std::endl;
		closesocket(*socket);
		*socket = INVALID_SOCKET;
		//WSACleanup();
		return SEND_ERR; // connection error code: 2
	}

	return iResult; // success code: 0;
}

int NonBlockingSocket::receiveNB(SOCKET* socket, char* buffer, int bufferLength, int continueFrom) {
	int iResult = 0, i = 0;
	int sockAddrLen = sizeof(struct sockaddr);
	FD_SET set;
	timeval timeVal;
	FD_ZERO(&set);
	// Add socket we will wait to read from
	FD_SET(*socket, &set);

	// Set timeouts to zero since we want select to return
	// instantaneously
	timeVal.tv_sec = 0;
	timeVal.tv_usec = 0;

	iResult = select(0 /* ignored */, &set, NULL, NULL, &timeVal);

	// lets check if there was an error during select
	if (iResult == SOCKET_ERROR)
	{
		std::cout << stderr << "select failed with error: %ld\n" << WSAGetLastError() << std::endl;
		return SOCK_ERR; //error code: -1
	}

	// now, lets check if there are any sockets ready
	if (iResult == 0)
	{
		// there are no ready sockets, sleep for a while and check again
		Sleep(SLEEP_TIME);
		return SLEEP; // sleep code: 1
	}


	// Receive data until the client shuts down the connection
	iResult = recv(*socket, buffer + continueFrom, bufferLength, 0);
	if (iResult > 0)
	{
		std::cout << "message received from client: " << buffer << std::endl;
	}
	else if (iResult == 0)
	{
		// connection was closed gracefully
		std::cout <<  "Connection with client closed."  << std::endl;
		//closesocket(*socket);
		//*socket = INVALID_SOCKET;
		return 0;
	}
	else
	{
		// there was an error during recv
		std::cout << "recv failed with error: %ld\n" << WSAGetLastError() << std::endl;
		//closesocket(*socket);
		//*socket = INVALID_SOCKET;
		//WSACleanup();
		return REC_ERR;
	}


	return iResult; // success code: 0;
}

int NonBlockingSocket::SEND(SOCKET* socket, char* buffer, int length) {

	int i = 0;
	int len = 0;
	if (length == 4) {
		len = *((int *)buffer);
	}
	else
		len = getMessageLength(buffer) + 6;

	int iResult = 0;

	while (i < len) {
		do {
			if(length == 4)
				iResult = sendNB(socket, buffer, len - i);
			else
				iResult = sendNB(socket, buffer, 12 - i);

		} while (iResult == SLEEP);
		if (iResult == SOCKET_ERROR)
		{
			std::cout << "sendto failed with error: %ld\n" << WSAGetLastError() << std::endl;
			closesocket(*socket);
			*socket = INVALID_SOCKET;
			//WSACleanup();
			return SEND_ERR; // connection error code: 2
		}
		i += iResult;
	}

	return iResult; // success code: 0
}


int NonBlockingSocket::RECEIVE(SOCKET* socket, char* buffer, int length) {

	int i = 0;
	int len;
	int iResult = 0;

	char *duzina = new char[length];
	while (i < length) {
		do {
			iResult = receiveNB(socket, duzina, length - i, 0);
			if (iResult == 0)  // konekcija je zatvorena, nema potrebe raditi ista dalje
				return 0;
		} while (iResult == SLEEP);
		if (iResult == SOCKET_ERROR)
		{
			std::cout <<  "receiving lenght failed with error" << WSAGetLastError() << std::endl;
			//closesocket(*socket);
			//socket = INVALID_SOCKET;
			//WSACleanup();
			return REC_ERR; // connection error code: 2
		}
		i += iResult;
	}
	if (length == 4) {
		len = *(int*)duzina;
	}
	else {
		len = getMessageLength(duzina);
		len = ntohs(len);
	}
	memcpy(buffer, duzina, length);
	delete duzina, duzina = 0;
	if (length != 4) {
		i = length;
		len += i - 1;
	}
	iResult = 0;
	while (i < len) {
		do {
			iResult = receiveNB(socket, buffer, len - i, i);
		} while (iResult == SLEEP);
		if (iResult == SOCKET_ERROR)
		{
			std::cout << "receiving the whole message failed with error: %ld\n" << WSAGetLastError() << std::endl;
			closesocket(*socket);
			//socket = INVALID_SOCKET;
			//WSACleanup();
			return REC_ERR; // connection error code: 2
		}
		i += iResult;
	}

	return i; // success code: 0
}


int NonBlockingSocket::getMessageLength(char *data) {
	return *((short*)data + 2);
}