#pragma once
#ifndef  TCP_RECEIVE_H
#define TCP_RECEIVE_H
#include "TCPState.h"
#include "TCPConnect.h"
#include "TCPActive.h"
class TCPReceive : public TCPState {
public:
	static TCPState* Instance();
	virtual void send(TCPConnection*);
};

#endif