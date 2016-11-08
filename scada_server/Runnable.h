#pragma once
#ifndef RUNNABLE_H
#define RUNNABLE_H
#include "stdafx.h"
class Runnable {
public:
	virtual void* run() = 0;
	virtual~Runnable() = 0;
};


#endif // !RUNNABLE_H

