#pragma once
#ifndef  TCP_RECEIVE_H
#define TCP_RECEIVE_H
#include "TCPState.h"
#include "TCPIdle.h"
#include "TCPClose.h"
class TCPReceive : public TCPState {
public:
	static TCPState* Instance();
	virtual void receive(TCPConnection*);
};

#endif