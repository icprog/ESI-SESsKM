#pragma once
#ifndef  MESSAGE_H
#define MESSAGE_H
#include "TCPHeader.h"
class Message {
protected:
	TCPHeader *tcpHeader;
public:
	Message(TCPHeader *tcpHeader_) : tcpHeader(tcpHeader_) {}
	TCPHeader *getTCPHeader();
};

#endif // ! MESSAGE_H
