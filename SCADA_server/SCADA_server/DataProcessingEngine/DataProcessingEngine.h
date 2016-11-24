#pragma once
#ifndef  DATA_PROCESSING_ENGINE_H
#define DATA_PROCESSING_ENGINE_H
#include "stdafx.h"
#include "../Util/BlockingQueue.h"
#include "../Util/Buffer.h"
#include "../Util/Util.h"
#include "../Model/AnalogInput.h"
#include "../Model/RemoteTelemetryUnit.h"
#include "../ModbusTCPDriver/TCPDriver.h"
class DataProcessingEngine {

public:
	DataProcessingEngine() { }
	DataProcessingEngine(BlockingQueue<char *> *m_sharedBuffer, BlockingQueue<char *> *streamBuffer_, BlockingQueue<char *> *alarmBuffer_, RemoteTelemetryUnit *m_rtu) : sharedBuffer(m_sharedBuffer),streamBuffer(streamBuffer_),alarmBuffer(alarmBuffer_), rtu(m_rtu) {

		std::thread dataProccesingEngineThread(DataProcessingEngine::process, this);
		//dataProccesingEngineThread.
		dataProccesingEngineThread.detach();
	}
	//DataProcessingEngine(Buffer *m_streamBuffer, RemoteTelemetryUnit *m_rtu) : streamBuffer(m_streamBuffer), rtu(m_rtu) {}
	//DataProcessingEngine(Buffer *m_streamBuffer, Buffer *m_sharedBuffer, RemoteTelemetryUnit *m_rtu) : streamBuffer(m_streamBuffer), sharedBuffer(m_sharedBuffer), rtu(m_rtu) {}
	~DataProcessingEngine() {
		delete streamBuffer, streamBuffer = 0;
		delete sharedBuffer, sharedBuffer = 0;
		delete alarmBuffer, alarmBuffer = 0;
		delete rtu, rtu = 0;
	}

	BlockingQueue<char *> *getStreamBuffer() { return streamBuffer; }
	BlockingQueue<char *> *getSharedBuffer() { return sharedBuffer; }
	BlockingQueue<char *> *getAlarmBuffer() { return alarmBuffer; }
	RemoteTelemetryUnit *getRTU() { return rtu; }
	void setStreamBuffer(BlockingQueue<char *> *newStreamBuffer) { streamBuffer = newStreamBuffer; }
	void setSharedBuffer(BlockingQueue<char *> *newSharedBuffer) { sharedBuffer = newSharedBuffer; }
	void setRTU(RemoteTelemetryUnit *newRTU) { rtu = newRTU; }

	static void process(DataProcessingEngine *that);
	void pushInStreamBuffer(DigitalDevice *dd, AnalogInput *it);
	void makeAlarm(DataProcessingEngine *that,Alarm *alarm);
	void turnHeaterOn(DataProcessingEngine *that, DigitalDevice *dd, short *command);
	void turnHeaterOff(DataProcessingEngine *that, DigitalDevice *dd, short *command);

	bool turnedOn(DigitalDevice * dd);

	bool isError(DigitalDevice * dd);
	
	//char * makeClientMessage();

private:
	BlockingQueue<char *> *streamBuffer;
	BlockingQueue<char *> *sharedBuffer;
	BlockingQueue<char *> *alarmBuffer;

	RemoteTelemetryUnit *rtu;
};

#endif // ! DATA_PROCESSING_ENGINE_H