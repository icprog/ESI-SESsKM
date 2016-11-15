#pragma once
#ifndef  UTIL_H
#define UTIL_H
#include "TCPHeader.h"
#include "RTU.h"
class Util {

public:
	static void initialize(char *, char*, int startIdx, int endIdx, int j);
	static void readFromFile(RTU *rtu);
};

#endif // ! UTIL_H
