#pragma once
#ifndef  TCP_CONNECT_H
#define TCP_CONNECT_H
#include "TCPState.h"
#include "TCPConnect.h"
#include "TCPActive.h"
class TCPConnect : public TCPState {
public:
	static TCPState* Instance();
	virtual void send(TCPConnection*);
};

#endif