#include "stdafx.h"
#include "TCPDriver.h"

char * TCPDriver::createRequest(char functionCode, char * startingAddress, char * quantityOfCoils)
{
	char request[12];
	request[0] = 0x01;
	request[1] = 0x00;
	request[2] = 0x00;
	request[3] = 0x00;
	request[4] = 0x06;
	request[5] = 0x00;
	request[6] = 0x00;
	request[7] = functionCode;
	request[8] = startingAddress[1];
	request[9] = startingAddress[0];
	request[10] = quantityOfCoils[1];
	request[11] = quantityOfCoils[0];
	return request;
}

int TCPDriver::sendRequest(char * request)
{
	int iResult = -1;
	// Send an prepared message with null terminator included

	cout << "\nSENDING MESSAGE: %s" << request << endl;

	iResult = nonBlockingSocket->SEND(&sock, request, 0);

	if (iResult == SOCKET_ERROR)
	{
		cout << "send failed with error: %d\n" << WSAGetLastError() << endl;
		closesocket(sock);
		//WSACleanup();
		return 1;
	}

	cout << "\nMESSAGE SENT! Bytes Sent: %ld\n" << iResult << endl;
	return 0;
}

int TCPDriver::tcpConnect()
{
	int iResult = -1;
	iResult = createSocket(); //1 is nonBlockingMode

	if (iResult != 0) {
		//WSACleanup();

		// ERROR
	}
	return iResult;
}

int TCPDriver::tcpCloseConnection()
{
	closesocket(sock);
	return 0;
}

int TCPDriver::createSocket()
{

	// create a socket
	sock = socket(AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP);

	if (sock == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		//WSACleanup();
		return 1; //fail!
	}

	// create and initialize address structure
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(ipAddress);
	serverAddress.sin_port = htons(port);
	// connect to server specified in serverAddress and socket connectSocket
	if (connect(sock, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		printf("Unable to connect to server.\n");
		closesocket(sock);
		//WSACleanup();
		return 1;
	}



	return 0;
}



int TCPDriver::selectt(int type) // 0 is receive, 1 is send
{
	FD_SET set;
	timeval timeVal;
	int iResult;

	do {
		iResult = 0;
		FD_ZERO(&set);
		// Add socket we will wait to read from
		FD_SET(sock, &set);

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

	} while (iResult == 0 && *exit == 0);

	return iResult;
}

SOCKET * TCPDriver::getSocket() const
{
	return &sock;
}

void TCPDriver::setSocket(SOCKET * socket)
{
	sock = *socket;
}

char * TCPDriver::getIpAddress() const
{
	return ipAddress;
}

void TCPDriver::setIpAddress(char * ipAddress)
{
	this->ipAddress = ipAddress;
}

int TCPDriver::getPort() const
{
	return port;
}

void TCPDriver::setPort(int port)
{
	this->port = port;
}
