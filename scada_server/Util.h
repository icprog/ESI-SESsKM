#pragma once
#ifndef  UTIL_H
#define UTIL_H
#include "TCPHeader.h"
#include "RTU.h"
class Util {

public:
	static void initialize(char *, char*, int startIdx, int endIdx, int j);
	static RTU *readFromFile();
};

#endif // ! UTIL_H
