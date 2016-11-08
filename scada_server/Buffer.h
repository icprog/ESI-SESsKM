#pragma once

#include "stdafx.h"
#include<iostream>
#include <windows.h>
using namespace std;

class Buffer {
private:
		char *name;
		char *data;
		int pushIdx;
		int popIdx;
		int count;
		int size;
		CRITICAL_SECTION cs;
public:
	void expand();		//exprend buffer size
	int push(char *data);		//adding data to buffer	
	int pop(char *data);		//remove data from buffer
	void shrink();		//shrink buffer
	void createBuffer(char *name, int bufferLength, CRITICAL_SECTION *cs);		//create buffer
	~Buffer();		//destructor

};
