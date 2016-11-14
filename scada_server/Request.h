#pragma once
#ifndef  REQUEST_H
#define REQUEST_H
#include "Message.h"
#include "Util.h"
#include "PDU.h"
class Request : public Message {
private:
	PDU *pdu;
	char request[12];
public:
	Request(TCPHeader *th, PDU *pdu_) : Message(th), pdu(pdu_) {
		createRequest();
	}
	void createRequest();
	char * getRequest();
};

#endif // ! REQUEST_H