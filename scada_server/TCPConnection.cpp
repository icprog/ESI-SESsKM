#include "stdafx.h"
#include "TCPConnection.h"
#include "TCPClose.h"

TCPConnection::TCPConnection() {
	_state = TCPClose::Instance();
}
void TCPConnection::connectt( SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b){
	_state->connectt(this, connectSocket, listenSocket, ipAddress, port, request, response, closeConnection, nonBlockingMode,b);
}
void TCPConnection::active( SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b){
	_state->active(this, connectSocket, listenSocket, ipAddress, port, request, response, closeConnection, nonBlockingMode,b);
}
void TCPConnection::send(SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b) {
	_state->send(this, connectSocket, listenSocket, ipAddress, port, request, response, closeConnection, nonBlockingMode,b);
}
void TCPConnection::receive(SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b) {
	_state->receive(this, connectSocket, listenSocket, ipAddress, port, request, response, closeConnection, nonBlockingMode,b);
}
void TCPConnection::close(SOCKET *connectSocket, SOCKET *listenSocket, char* ipAddress, int port, char *request, char *response, bool closeConnection, unsigned long int nonBlockingMode, Buffer *b) {
	_state->close(this, connectSocket, listenSocket, ipAddress, port, request, response, closeConnection, nonBlockingMode,b);
}
void TCPConnection::ChangeState(TCPState* s) {
	_state = s;
}

/*
	GET
	SET
*/
int TCPConnection::getConnectionEstablished() const {
	return connectionEstablished;
}
int TCPConnection::getSendAndReceive() const {
	return sendAndReceive;
}
int TCPConnection::getSendClosesConnection() const {
	return sendClosesConnection;
}
int TCPConnection::getReceiveClosesConnection() const {
	return receiveClosesConnection
}
void TCPConnection::setConnectionEstablished(int val) {
	connectionEstablished = val;
}
void TCPConnection::setSendAndReceive(int val) {
	sendAndReceive = val;
}
void TCPConnection::setSendClosesConnection(int val) {
	sendClosesConnection = val;
}
void TCPConnection::setReceiveClosesConnection(int val) {
	receiveClosesConnection = val;
}

