#include "TCPSend.h"

void TCPSend::send(TCPConnection *t, SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode) {
	int iResult = -1;
	iResult = sendMessage(connectSocket, request);
	if (iResult != 0) {
	// ERROR
	}

	if(closeConnection == true){
		ChangeState(t, TCPClose::Instance());
		t->close(connectSocket, nullptr, nullptr, -1, nullptr, nullptr, false, -1);
	}
	if (response != nullptr){
		ChangeState(t, TCPReceive::Instance());
		t->receive(connectSocket, listenSocket, ipAddress, port, request, response, closeConnection, nonBlockingMode);
	}
	else{
		ChangeState(t, TCPActive::Instance());
		t->active(connectSocket, listenSocket, ipAddress, port, request, response, closeConnection, nonBlockingMode);
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

	printf("\nSENDING MESSAGE: %s", data + 9);
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