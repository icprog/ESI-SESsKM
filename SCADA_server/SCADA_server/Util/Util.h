#pragma once
#ifndef  UTIL_H
#define UTIL_H
#include<iostream>
#include <string>
#include "pugixml.h"
#include "BlockingQueue.h"
#include "../Model/RemoteTelemetryUnit.h"
#include "../Model/AnalogInput.h"
#include "../Model/DigitalDevice.h"

class Util {

public:
	static RemoteTelemetryUnit *parseXMLConfig();
	static int getSharedMesageSize(BlockingQueue<char *> *sharedBuffer);
	static int getSharedResponseSize(BlockingQueue<char *> *sharedBuffer);
	static void createRequest(char *request, DigitalDevice *dd, AnalogInput *ai, AnalogOutput *ao, int type, short value); //0 = write, 1 read
};

#endif // ! UTIL_H

