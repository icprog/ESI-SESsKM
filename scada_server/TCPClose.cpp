#include "TCPClose.h"

void TCPClose::close(TCPConnection *t, SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode) {
	if (connectSocket != nullptr) {

		closesocket(*connectSocket);

		ChangeState(t, TCPClose::Instance());

	}
	else{
		ChangeState(t, TCPConnect::Instance());
		t->connectt(connectSocket, ipAddress, port);
	}

}