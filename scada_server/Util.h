#pragma once
#ifndef  UTIL_H
#define UTIL_H
#include "TCPHeader.h"
class Util {

public:
	static void initialize(char *, char*, int startIdx, int endIdx, int j);
	static void readFromFile();
};

#endif // ! UTIL_H