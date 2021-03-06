#include "stdafx.h"
#include "TCPDriver.h"

void TCPDriver::createRequest(char *req, char *whole_req)
{

	whole_req[0] = 0x01;
	whole_req[1] = 0x00;
	whole_req[2] = 0x00;
	whole_req[3] = 0x00;
	whole_req[4] = 0x06;
	whole_req[5] = 0x00;
	whole_req[6] = 0x00;
	whole_req[7] = req[0];
	whole_req[8] = req[1];
	whole_req[9] = req[2];
	whole_req[10] = req[3];
	whole_req[11] = req[4];



}

int TCPDriver::sendRequest(char * request)
{
	int iResult = -1;
	// Send an prepared message with null terminator included

	//std::cout << "\nSENDING MESSAGE: %s" << request << std::endl;

	iResult = nonBlockingSocket->SEND(&sock, request, 0);

	if (iResult == SOCKET_ERROR)
	{
		std::cout << "send failed with error: %d\n" << WSAGetLastError() << std::endl;
		closesocket(sock);
		//WSACleanup();
		return 1;
	}

	std::cout << "\nMESSAGE SENT! Bytes Sent: %ld\n" << iResult << std::endl;
	receiveResponse(request);
	return 0;
}

int TCPDriver::receiveResponse(char *request)
{
	int iResult = -1;
	char response[512];
	do {
		iResult = nonBlockingSocket->RECEIVE(&sock, response, 7);
		std::cout << iResult << std::endl;
		if (iResult > 0)
		{
			std::cout << "Message received modbus simulator: %s.\n" << response << std::endl;

			// prvo proveri sta ima da se radi
			if (response[7] == 0x80 || response[7] == (0x80 + request[7])) {
				std::cout << "Modbus simulator returned an error. Please try again." << std::endl;
			}
			else if (response[7] != request[7]) {
				std::cout << "Value probably already written." << std::endl;
			}
			if (request[7] == 0x05)
				break;
			char *wholeMessage;
			int len = *((short*)response + 2);
			len = ntohs(len);
			len += 6;
			int wholeMessageSize = 8 + 12 + len; // 4 duzina cele poruke, 4 za len, len za responsem, 12 duzina requesta

			wholeMessage = new char[wholeMessageSize];
			*(int *)wholeMessage = wholeMessageSize;
			*((int *)wholeMessage + 1) = len;

			int j = 0;
			for (int i = 8; i < len + 8; i++) {
				wholeMessage[i] = response[j];
				j++;
			}
			j = 0;
			for (int i = 8 + len; i < 20 + len; i++) {
				wholeMessage[i] = request[j];
				j++;
			}

			sharedBuffer->push(wholeMessage);  // SMESTITI U BAFER!
			//delete wholeMessage, wholeMessage = 0;
			try
			{
				delete request, request = 0;
			}
			catch (...)
			{}
			
			iResult = 0;
		}
		if (iResult == 0)
		{
			// connection was closed gracefully
			std::cout << "Message received. Finishing." << std::endl;
			//closesocket(*acceptedSocket);
			break;
		}
		else
		{
			// there was an error during recv
			std::cout << "recv failed with error: %d\n" << WSAGetLastError() << std::endl;
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
		std::cout << "socket failed with error: %ld\n" << WSAGetLastError() << std::endl;
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
		std::cout << "Unable to connect to server.\n" << std::endl;
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
			std::cout << stderr<< "select failed with error: %ld\n"<< WSAGetLastError() << std::endl;
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

SOCKET * TCPDriver::getSocket()
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

