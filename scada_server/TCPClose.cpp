#include "TCPClose.h"

void TCPClose::close(TCPConnection* t) {
	/*
		Zatvara se konekcija i sve se unistava
	*/

	// promena stanja
	if(1) // smisliti uslov
		ChangeState(t, TCPClose::Instance());
	else
		ChangeState(t, TCPConnect::Instance());
}