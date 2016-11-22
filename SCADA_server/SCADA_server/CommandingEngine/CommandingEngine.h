#pragma once
#ifndef  COMMANDING_ENGINE_H
#define COMMANDING_ENGINE_H
#include "stdafx.h"

class CommandingEngine {

public:
	CommandingEngine() {}
	CommandingEngine(Buffer *streamBuffer_, Buffer *commandingBuffer_, Buffer *sharedBuffer_, RemoteTelemetryUnit *rtu_) :
		streamBuffer(streamBuffer_), commandingBuffer(commandingBuffer_), sharedBuffer(sharedBuffer_), rtu(rtu_) {
		std::thread commandingEnginePopThread(CommandingEngine::popCommand, this);
		commandingEnginePopThread.detach();

		std::thread commandingEngineClosedLoopThread(CommandingEngine::closedLoop, this);
		commandingEngineClosedLoopThread.detach();
	}
	~CommandingEngine() {}
	static void popCommand(CommandingEngine *that);
	static void closedLoop(CommandingEngine *that);
	Buffer *getStreamBuffer() { return streamBuffer; }
	Buffer *getCommandingBuffer() { return commandingBuffer; }
	Buffer *getSharedBuffer() { return sharedBuffer; }
	RemoteTelemetryUnit *getRTU() { return rtu; }
	char *getResponse() { return response; }
	int getResponseSize() { return *(int *)response; }
	bool turnedOn(CommandingEngine *that);

private:
	Buffer *streamBuffer;
	Buffer *commandingBuffer;
	Buffer *sharedBuffer;
	RemoteTelemetryUnit *rtu;
	int turnHeaterOn(CommandingEngine * that);
	int turnHeaterOff();
	void sendRequest();
	void receiveResponse();
	void makeAlarm(CommandingEngine *that);
	char *response = nullptr;
	// TCPDriver::getInstance()

};

#endif // ! COMMANDING_ENGINE_H