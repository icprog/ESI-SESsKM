#pragma once
#ifndef  TCP_CLOSE_H
#define TCP_CLOSE_H
#include "TCPState.h"
#include "TCPConnect.h"
#include "TCPActive.h"
class TCPClose : public TCPState {
public:
	static TCPState* Instance();
	virtual void send(TCPConnection*);
};

#endif