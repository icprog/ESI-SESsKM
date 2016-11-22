#pragma once
#ifndef  UTIL_H
#define UTIL_H
#include<iostream>
#include <string>
#include "pugixml.h"
#include "Buffer.h"
#include "../Model/RemoteTelemetryUnit.h"
#include "../Model/AnalogInput.h"
#include "../Model/DigitalDevice.h"

class Util {

public:
	static RemoteTelemetryUnit *parseXMLConfig();
	static int getSharedMesageSize(Buffer *sharedBuffer);
	static int getSharedResponseSize(Buffer *sharedBuffer);
	static void createRequest(char *request, DigitalDevice *dd, AnalogInput *ai, AnalogOutput *ao, int type); //0 = write, 1 read
};

#endif // ! UTIL_H

