#include "TCPIdle.h"

void TCPIdle::connect(TCPConnection *t) {

	// KONEKCIJA
	/*
	
	
	
	
	*/

	if (t->getConnectionEstablished)
		ChangeState(t, TCPConnect::Instance());
	else
		ChangeState(t, TCPActive::Instance());

}