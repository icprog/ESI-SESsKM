#pragma once
#ifndef  DATA_PROCESSING_ENGINE_H
#define DATA_PROCESSING_ENGINE_H

class DataProcessingEngine {
public:
	DataProcessingEngine() {}
	~DataProcessingEngine() {}

	void process();
	char * makeClientMessage();
private:
	//Buffer *streamBuffer;
	//Buffer *sharedBuffer;
	//RTU *rtu;

};

#endif // ! DATA_PROCESSING_ENGINE_H