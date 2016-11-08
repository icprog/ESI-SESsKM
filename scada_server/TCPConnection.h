#pragma once
#ifndef  TCP_CONNECTION_H
#define TCP_CONNECTION_H

/*
	Context class that is used for changing the state of the state machine.
*/
class TCPConnection {

public:
	TCPConnection();
	void idle();
	void connect();
	void active();
	void send();
	void receive();
	void close();
	int getConnectionEstablished() const;
	int getSendAndReceive() const;
	int getSendClosesConnection() const;
	int getReceiveClosesConnection() const;
	void setConnectionEstablished(int);
	void setSendAndReceive(int);
	void setSendClosesConnection(int) ;
	void setReceiveClosesConnection(int) ;
private:
	friend class TCPState;
	void ChangeState(TCPState*);
private:
	TCPState* _state;
	int connectionEstablished = 0;
	int sendAndReceive = 0;
	int sendClosesConnection = 0;
	int receiveClosesConnection = 0;
};

#endif // ! TCP_CONNECTION_H