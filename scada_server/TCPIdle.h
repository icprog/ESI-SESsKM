#pragma once
#ifndef  TCP_IDLE_H
#define TCP_IDLE_H
#include "TCPState.h"
#include "TCPConnect.h"
#include "TCPActive.h"
class TCPIdle : public TCPState {
public:
	static TCPState* Instance();
	virtual void connect(TCPConnection*);
};

#endif
