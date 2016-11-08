#include "stdafx.h"
#include "TCPConnection.h"
#include "TCPIdle.h"

TCPConnection::TCPConnection() {
	_state = TCPClose::Instance();
}
void TCPConnection::connect() {
	_state->connect(this);
}
void TCPConnection::active() {
	_state->active(this);
}
void TCPConnection::send() {
	_state->send(this);
}
void TCPConnection::receive() {
	_state->receive(this);
}
void TCPConnection::close() {
	_state->close(this);
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