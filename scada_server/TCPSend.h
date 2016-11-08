#pragma once
#ifndef  TCP_SEND_H
#define TCP_SEND_H
#include "TCPState.h"
#include "TCPClose.h"
#include "TCPReceive.h"
class TCPSend : public TCPState {
public:
	static TCPState* Instance();
	virtual void send(TCPConnection*);
};

#endif