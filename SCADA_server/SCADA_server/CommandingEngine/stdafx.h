// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



// TODO: reference additional headers your program requires here
#include "../Util/Buffer.h"
#include "../Util/Stopwatch.h"
#include "../Util/Util.h"
#include "../Model/RemoteTelemetryUnit.h"
#include "../ModbusTCPDriver/TCPDriver.h"
#include "../Model/DigitalDevice.h"
#include <thread>
#include <iostream>