#pragma once
#ifndef  TCP_STATE_H
#define TCP_STATE_H
#include "TCPConnection.h"
#include "Buffer.h"
class TCPState {
public:
	virtual void connectt(TCPConnection *, SOCKET *, SOCKET *, char*, int, char *, char *, bool, unsigned long int, Buffer *) {}
	virtual void active(TCPConnection *, SOCKET *, SOCKET *, char*, int, char *, char *, bool, unsigned long int, Buffer *) {}
	virtual void send(TCPConnection *, SOCKET *, SOCKET *, char*, int, char *, char *, bool, unsigned long int, Buffer *) {}
	virtual void receive(TCPConnection *, SOCKET *, SOCKET *, char*, int, char *, char *, bool, unsigned long int, Buffer *) {}
	virtual void close(TCPConnection *, SOCKET *, SOCKET *, char*, int, char *, char *, bool, unsigned long int, Buffer *) {}
protected:
	void ChangeState(TCPConnection*, TCPState*);
};

#endif // ! TCP_STATE_H