#include "stdafx.h"
#include "TCPDriver.h"

char * TCPDriver::createRequest(char *req)
{
	char request[12];
	request[0] = 0x01;
	request[1] = 0x00;
	request[2] = 0x00;
	request[3] = 0x00;
	request[4] = 0x06;
	request[5] = 0x00;
	request[6] = 0x00;
	request[7] = req[0];
	request[8] = req[1];
	request[9] = req[2];
	request[10] = req[3];
	request[11] = req[4];
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
	receiveResponse(request);
	return 0;
}

int TCPDriver::receiveResponse(char *request)
{
	int iResult = -1;
	char response[512];
	do {
		iResult = nonBlockingSocket->RECEIVE(&sock, response, 0);
		cout << iResult << endl;
		if (iResult > 0)
		{
			cout << "Message received from server as a server: %s.\n" << response << endl;

			// prvo proveri sta ima da se radi
			if (response[7] == 0x80 || response[7] == (0x80 + request[7])) {
				return -1;
			}

			char *wholeMessage;
			int len = *((short*)response + 2);
			len = ntohs(len);
			len += 6;
			int wholeMessageSize = 4 + 12 + len; // 4 duzina cele poruke, 12 duzina requesta, i len je duzina responsa
			
			wholeMessage = new char[wholeMessageSize];
			*(int *)wholeMessage = wholeMessageSize;
			*((int *)wholeMessage + 1) = len;

			memcpy(wholeMessage+8, response, len);
			memcpy(wholeMessage + 8 + len, request, 12);

			//b->push(wholeMessage, 0);  // SMESTITI U BAFER!
			delete wholeMessage, wholeMessage = 0;
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
