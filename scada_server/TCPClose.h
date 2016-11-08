#pragma once
#ifndef  TCP_CLOSE_H
#define TCP_CLOSE_H
#include "TCPState.h"
#include "TCPIdle.h"
class TCPClose : public TCPState {
public:
	static TCPState* Instance();
	virtual void close(TCPConnection*);
};

#endif