#pragma once
#ifndef  DATA_PROCESSING_ENGINE_H
#define DATA_PROCESSING_ENGINE_H
#include "stdafx.h"
#include "../Util/Buffer.h"
#include "../Util/Util.h"
#include "../Model/AnalogInput.h"
#include "../Model/RemoteTelemetryUnit.h"

class DataProcessingEngine {

public:
	DataProcessingEngine() {}
	DataProcessingEngine(Buffer *m_streamBuffer, RemoteTelemetryUnit *m_rtu) : streamBuffer(m_streamBuffer), rtu(m_rtu) {}
	DataProcessingEngine(Buffer *m_streamBuffer, Buffer *m_sharedBuffer, RemoteTelemetryUnit *m_rtu) : streamBuffer(m_streamBuffer), sharedBuffer(m_sharedBuffer), rtu(m_rtu) {}
	~DataProcessingEngine() {}

	Buffer getStreamBuffer() { return *streamBuffer; }
	Buffer getSharedBuffer() { return *sharedBuffer; }
	RemoteTelemetryUnit getRTU() { return *rtu; }
	void setStreamBuffer(Buffer *newStreamBuffer) { streamBuffer = newStreamBuffer; }
	void setSharedBuffer(Buffer *newSharedBuffer) { sharedBuffer = newSharedBuffer; }
	void setRTU(RemoteTelemetryUnit *newRTU) { rtu = newRTU; }

	void process(Buffer *sharedBuffer, RemoteTelemetryUnit *rtu);
	//char * makeClientMessage();

private:
	Buffer *streamBuffer;
	Buffer *sharedBuffer;
	RemoteTelemetryUnit *rtu;
};

#endif // ! DATA_PROCESSING_ENGINE_H