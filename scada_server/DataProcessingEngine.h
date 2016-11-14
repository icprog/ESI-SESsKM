#pragma once
#ifndef  DATA_PROCESSING_ENGINE_H
#define DATA_PROCESSING_ENGINE_H
#include "Buffer.h"
#include "RTU.h"
#include <vector>
#define DEFAULT_BUFLEN 512
class DataProcessing {
public:
	DataProcessing() {}
	void dataProcessingEngine(Buffer *recvBuf, /*char * data,*/ RTU * rtu);
	~DataProcessing() {}
private:
	//Buffer *myBuffer;
	//char *data;
	//RTU rtu;
};

#endif // ! ICOMPONENT_MEDIATOR_H
