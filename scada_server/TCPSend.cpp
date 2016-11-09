#include "stdafx.h"
#include "TCPSend.h"

void TCPSend::send(TCPConnection *t, SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b) {
	
	int iResult = -1;
	iResult = sendMessage(connectSocket, request);
	if (iResult != 0) {
	// ERROR
	}

	if(closeConnection == true){
		TCPClose *tcpClose = new TCPClose();

		ChangeState(t, tcpClose);
		t->close(connectSocket, nullptr, nullptr, -1, nullptr, nullptr, false, -1,b);
		delete tcpClose, tcpClose = 0;
	}
	if (response != nullptr){
		TCPReceive *tcpReceive = new TCPReceive();

		ChangeState(t, tcpReceive);
		t->receive(connectSocket, listenSocket, ipAddress, port, request, response, closeConnection, nonBlockingMode,b);
		delete tcpReceive, tcpReceive = 0;
	}
	else{
		TCPActive *tcpActive = new TCPActive();

		ChangeState(t, tcpActive);
		t->active(connectSocket, listenSocket, ipAddress, port, request, response, closeConnection, nonBlockingMode,b);
		delete tcpActive, tcpActive = 0;
	}

}
int TCPSend::createSocket(SOCKET * ssocket, char * ip, int port)
{
	// create a socket
	*ssocket = socket(AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP);

	if (*ssocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		//WSACleanup();
		return 1; //fail!
	}

	// create and initialize address structure
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(ip);
	serverAddress.sin_port = htons(port);
	// connect to server specified in serverAddress and socket connectSocket
	if (connect(*ssocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		printf("Unable to connect to server.\n");
		closesocket(*ssocket);
		//WSACleanup();
		return 1;
	}

	return 0;
}

int TCPSend::sendMessage(SOCKET * socket, char * data)
{
	int iResult = -1;
	// Send an prepared message with null terminator included

	printf("\nSENDING MESSAGE: %s", data );
	SocketNB *snb = new SocketNB();
	iResult = snb->SEND(socket, data);
	delete snb, snb = 0;
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