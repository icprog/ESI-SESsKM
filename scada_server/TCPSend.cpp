#include "TCPSend.h"

void TCPSend::send(TCPConnection* t) {
	/*
		RADI SE NEKI SEND
	*/

	// promena stanja
	if (t->getSendClosesConnection)
		ChangeState(t, TCPClose::Instance());
	else
		ChangeState(t, TCPReceive::Instance());
}