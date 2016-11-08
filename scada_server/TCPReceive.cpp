#include "TCPReceive.h"

void TCPReceive::receive(TCPConnection* t) {
	/*
		RADI SE NEKI RECEIVE
	*/

	// promena stanja
	ChangeState(t, TCPClose::Instance()); //nemoj zatvoriti konekciju!
}