#include "stdafx.h"
#include "TCPHeader.h"


TCPHeader::TCPHeader(char *tId, char *pId, char *len, char uId) {
	Util::initialize(transactionId, tId,0, 2, 0);
	Util::initialize(protocolId, pId, 0, 2, 0);
	Util::initialize(length, len, 0, 2, 0);
	unitIdentifier = uId;
	createTcpHeader();
}

void TCPHeader::createTcpHeader()
{
	Util::initialize(tcpHeader, transactionId, 0, 2, 0);
	Util::initialize(tcpHeader, protocolId, 0,2,2);
	Util::initialize(tcpHeader, length, 0,2,4);
	char t[1];
	t[0] = unitIdentifier;
	Util::initialize(tcpHeader, t, 0,1,6);
}

char * TCPHeader::getTCPHeader()
{
	return tcpHeader;
}
