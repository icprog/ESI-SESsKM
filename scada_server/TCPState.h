#pragma once
#ifndef  TCP_STATE_H
#define TCP_STATE_H
#include "TCPConnection.h"

class TCPState {
public:
	virtual void idle();
	virtual void connect(TCPConnection *);
	virtual void active(TCPConnection *);
	virtual void send(TCPConnection *);
	virtual void receive(TCPConnection *);
	virtual void close(TCPConnection *);
protected:
	void ChangeState(TCPConnection*, TCPState*);
};

#endif // ! TCP_STATE_H