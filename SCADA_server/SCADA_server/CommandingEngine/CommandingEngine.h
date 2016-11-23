#pragma once
#ifndef  COMMANDING_ENGINE_H
#define COMMANDING_ENGINE_H
#include "stdafx.h"

class CommandingEngine {

public:
	CommandingEngine() {}
	CommandingEngine(BlockingQueue<char *>  *commandingBuffer_, RemoteTelemetryUnit *rtu_) :
		commandingBuffer(commandingBuffer_), rtu(rtu_) {
		std::thread commandingEngineThread(CommandingEngine::popFromBuffer, this);
		commandingEngineThread.detach();
	}
	~CommandingEngine() {}
	BlockingQueue<char *>  *getCommandingBuffer() { return commandingBuffer; }
	static void popFromBuffer(CommandingEngine *that);
	RemoteTelemetryUnit * getRtu() { return rtu; }

	static void turnOnHeater(CommandingEngine *that);
	static void turnOffHeater(CommandingEngine *that);
	std::atomic<bool> *getHeaterOn() { return &heaterOn; }
private:
	BlockingQueue<char *> *commandingBuffer;
	RemoteTelemetryUnit *rtu;
	std::atomic<bool> heaterOn = false;

};

#endif // ! COMMANDING_ENGINE_H