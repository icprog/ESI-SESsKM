#include "stdafx.h"
#include "Request.h" 

void Request::createRequest()
{
	Util::initialize(request, tcpHeader->getTCPHeader(), 0, 7, 0);
	int j = 7;
	for (int i = 0; i < 5; i++, j++) {
		request[j] = pdu->getPDU()[i];
	}
}

char * Request::getRequest()
{
	return request;
}

