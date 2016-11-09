#include "stdafx.h"
#include "TCPClose.h"

void TCPClose::close(TCPConnection *t, SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b) {
	if (closeConnection) {

		closesocket(*connectSocket);

		TCPState *tcpClose = new TCPClose();
		ChangeState(t, tcpClose);
		t->close(nullptr, nullptr, nullptr, -1, nullptr, nullptr, false, -1, nullptr);
		delete tcpClose, tcpClose = 0;

	}
	else{
		TCPConnect *tcpConnect = new TCPConnect();
		ChangeState(t, tcpConnect);
		t->connectt(connectSocket, listenSocket, ipAddress, port, request, response, closeConnection, nonBlockingMode, b);
		delete tcpConnect, tcpConnect = 0;
	}

}