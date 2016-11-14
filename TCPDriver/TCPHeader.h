#pragma once
#ifndef  TCP_HEADER_H
#define TCP_HEADER_H
#pragma pack(1)
#include "../Util/Util.h"
class TCPHeader {
private:
	char transactionId[2];
	char protocolId[2];
	char length[2];
	char unitIdentifier;
	char tcpHeader[7];
public:
	void createTcpHeader();
	TCPHeader(char *tId, char *pId, char *len, char uId);
	char* getTCPHeader();
};

#endif // ! TCP_HEADER_H
