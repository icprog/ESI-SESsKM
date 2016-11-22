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
	DataProcessingEngine(Buffer *m_sharedBuffer,Buffer *streamBuffer_, RemoteTelemetryUnit *m_rtu) : sharedBuffer(m_sharedBuffer),streamBuffer(streamBuffer_), rtu(m_rtu) {
		std::thread dataProccesingEngineThread(DataProcessingEngine::process, this);
		dataProccesingEngineThread.detach();
	}
	//DataProcessingEngine(Buffer *m_streamBuffer, RemoteTelemetryUnit *m_rtu) : streamBuffer(m_streamBuffer), rtu(m_rtu) {}
	//DataProcessingEngine(Buffer *m_streamBuffer, Buffer *m_sharedBuffer, RemoteTelemetryUnit *m_rtu) : streamBuffer(m_streamBuffer), sharedBuffer(m_sharedBuffer), rtu(m_rtu) {}
	~DataProcessingEngine() {
		delete streamBuffer, streamBuffer = 0;
		delete sharedBuffer, sharedBuffer = 0;
		delete rtu, rtu = 0;
	}

	Buffer *getStreamBuffer() { return streamBuffer; }
	Buffer *getSharedBuffer() { return sharedBuffer; }
	RemoteTelemetryUnit *getRTU() { return rtu; }
	void setStreamBuffer(Buffer *newStreamBuffer) { streamBuffer = newStreamBuffer; }
	void setSharedBuffer(Buffer *newSharedBuffer) { sharedBuffer = newSharedBuffer; }
	void setRTU(RemoteTelemetryUnit *newRTU) { rtu = newRTU; }

	static void process(DataProcessingEngine *that);
	void pushInStreamBuffer(DigitalDevice *dd, AnalogInput *it);
	//char * makeClientMessage();

private:
	Buffer *streamBuffer;
	Buffer *sharedBuffer;
	RemoteTelemetryUnit *rtu;
};

#endif // ! DATA_PROCESSING_ENGINE_H