#include "TCPReceive.h"

void TCPReceive::receive(TCPConnection* t) {
	/*
		RADI SE NEKI RECEIVE
	*/

	// promena stanja
	if (t->getReceiveClosesConnection)
		ChangeState(t, TCPClose::Instance());
	else
		ChangeState(t, TCPActive::Instance());
}