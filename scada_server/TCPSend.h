#pragma once
#ifndef  TCP_SEND_H
#define TCP_SEND_H
#include "TCPState.h"
#include "TCPConnect.h"
#include "TCPActive.h"
class TCPSend : public TCPState {
public:
	static TCPState* Instance();
	virtual void send(TCPConnection*);
};

#endif