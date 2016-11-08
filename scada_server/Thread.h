#pragma once
#ifndef THREAD_H
#define THREAD_H
#include "stdafx.h"
#include <iostream>
#include <memory>
#include "Runnable.h"
#include <Windows.h>
#include <cassert>
#include <process.h>
class Thread {
public:
	Thread(std::unique_ptr<Runnable> runnable_);
	Thread();
	virtual~Thread();
	void start(); // starts a suspended thread
	void* join(); // wait for thread to complete
private:
	HANDLE hThread;
	unsigned winThreadID; // Win32 thread ID
	std::unique_ptr<Runnable> runnable;
	Thread(const Thread&);
	const Thread& operator=(const Thread&);
	void setCompleted(); // called when run() completes
	void* result; // stores value returned by run()
	virtual void* run() { return 0; }
	static unsigned WINAPI startThreadRunnable(LPVOID pVoid);
	static unsigned WINAPI startThread(LPVOID pVoid);
	void PrintError(LPTSTR lpszFunction, LPSTR fileName, int lineNumber);
	HANDLE completionEvent;
};

#endif