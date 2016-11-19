#pragma once
#ifndef  UTIL_H
#define UTIL_H
#include<iostream>
#include <string>
#include "pugixml.h"
#include "../Model/RemoteTelemetryUnit.h"
#include "../Model/AnalogInput.h"
#include "../Model/DigitalDevice.h"

class Util {

public:
	static RemoteTelemetryUnit *parseXMLConfig();
};

#endif // ! UTIL_H

