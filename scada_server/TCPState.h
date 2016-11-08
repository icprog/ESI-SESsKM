#pragma once
#ifndef  TCP_STATE_H
#define TCP_STATE_H
#include "TCPConnection.h"

class TCPState {
public:
	virtual void idle();
	virtual void connectt(TCPConnection *, SOCKET *, SOCKET *, char*, int, char *, char *, bool, unsigned long int);
	virtual void active(TCPConnection *, SOCKET *, SOCKET *, char*, int, char *, char *, bool, unsigned long int);
	virtual void send(TCPConnection *, SOCKET *, SOCKET *, char*, int, char *, char *, bool, unsigned long int);
	virtual void receive(TCPConnection *, SOCKET *, SOCKET *, char*, int, char *, char *, bool, unsigned long int);
	virtual void close(TCPConnection *, SOCKET *, SOCKET *, char*, int, char *, char *, bool, unsigned long int);
protected:
	void ChangeState(TCPConnection*, TCPState*);
};

#endif // ! TCP_STATE_H