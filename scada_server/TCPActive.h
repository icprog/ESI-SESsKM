#pragma once
#ifndef  TCP_ACTIVE_H
#define TCP_ACTIVE_H
#include "TCPState.h"
#include "TCPConnect.h"
#include "TCPActive.h"
class TCPActive : public TCPState {
public:
	static TCPState* Instance();
	virtual void send(TCPConnection*);
};

#endif