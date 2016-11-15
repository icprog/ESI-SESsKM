#pragma once
#ifndef  DATA_PROCESSING_ENGINE_H
#define DATA_PROCESSING_ENGINE_H
#include "Buffer.h"
#include "RTU.h"
#include "Thread.h"
#include <vector>
#define DEFAULT_BUFLEN 512
class DataProcessing : public Thread{
public:
	DataProcessing() {}
	DataProcessing(int threadId_, Buffer *buffer_, char *address_, RTU *rtu_) : threadId(threadId_), myBuffer(buffer_), address(address_), rtu(rtu_) {}
	void dataProcessingEngine(Buffer *recvBuf, char * sAddress, RTU * rtu);
	virtual void* run();
	~DataProcessing() {}
private:
	int threadId;
	Buffer *myBuffer;
	char *address;
	//char *data;
	RTU *rtu;
};

#endif // ! ICOMPONENT_MEDIATOR_H
