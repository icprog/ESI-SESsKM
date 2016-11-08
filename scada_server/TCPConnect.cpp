#include "TCPConnect.h"

void TCPConnect::connect(TCPConnection* t) {
	/*
	 RADI SE NEKI SEND
	*/

	// promena stanja
	ChangeState(t, TCPSend::Instance());
}