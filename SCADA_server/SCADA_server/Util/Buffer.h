
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
	int getPushIdx() { return pushIdx; }
	int getPopIdx() { return popIdx; }
	int getCount() { return count; }
	char *getData() { return data; }
	void expand();		
	int push(char *data, int sizeOfData);		//adding data to buffer	
	int pop(char *data, int velicina);		//remove data from buffer
	void shrink();		

	Buffer(char * _name, int _bufferLength) : name(_name), size(_bufferLength) {
		this->count = 0;
		this->popIdx = 0;
		this->pushIdx = 0;
		this->data = new char[_bufferLength + 1];
		memset(this->data, 0, _bufferLength);
		InitializeCriticalSection(&cs);
	}
	~Buffer();

};
