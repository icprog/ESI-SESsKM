#include "TCPClose.h"

void TCPClose::close(TCPConnection *t, SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b) {
	if (connectSocket != nullptr) {

		closesocket(*connectSocket);

		ChangeState(t, TCPClose::Instance());

	}
	else{
		ChangeState(t, TCPConnect::Instance());
		t->connectt(connectSocket, listenSocket, ipAddress, port, request, response, closeConnection, nonBlockingMode, b);
	}

}