#pragma once
#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "stdafx.h"
class Structure {
	char *message;
public:
	Structure(char *message_) :message(message_) {}
	Structure() {
		message = new char;
	}
	~Structure() {
		delete message, message = 0;
	}
	char *getMessage() { return message; }
	void setMessage(char *m, int size) { 
		message = new char[size];
		for (int i = 0; i < size; i++) {
			message[i] = m[i];
		}
	
	}
};

#endif