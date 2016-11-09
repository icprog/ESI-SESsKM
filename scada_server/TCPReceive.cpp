#include "stdafx.h"
#include "TCPReceive.h"

void TCPReceive::receive(TCPConnection *t, SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b) {
	SocketNB *snb = new SocketNB();
	int iResult = -1;
	do{
		iResult = snb->RECEIVE(connectSocket, response);
		printf("%d", iResult);
		if (iResult > 0)
		{
			printf("Message received from server as a server: %s.\n", response );
			b->push(response);
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

	delete snb, snb = 0;
	TCPClose *tcpClose = new TCPClose();
	ChangeState(t, tcpClose);
	t->close(connectSocket, nullptr, nullptr, -1, nullptr, nullptr, false, -1, nullptr);
	delete tcpClose, tcpClose = 0;
}