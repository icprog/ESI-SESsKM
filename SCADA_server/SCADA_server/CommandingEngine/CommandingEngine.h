#pragma once
#ifndef  COMMANDING_ENGINE_H
#define COMMANDING_ENGINE_H
#include "stdafx.h"

class CommandingEngine {

public:
	CommandingEngine() {}
	~CommandingEngine() {}
	void popCommand();
private:
	// Buffer *streamBuffer
	// Buffer *commandingBuffer
	// TCPDriver::getInstance()

};

#endif // ! COMMANDING_ENGINE_H