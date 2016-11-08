#include "stdafx.h"
#include "Thread.h"
Thread::Thread(std::unique_ptr<Runnable> runnable_) : runnable(std::move(runnable_)) {
	if (runnable.get() == NULL)
		printf("Thread(std::auto_ptr<Runnable> runnable_) failed at ",
			__FILE__, __LINE__);
	completionEvent = CreateEvent(
		NULL, // no security attributes
		1, // manual reset Event
		0, // initially nonsignaled
		NULL); // unnamed event
	hThread = (HANDLE)_beginthreadex(NULL, 0, Thread::startThreadRunnable,
		(LPVOID)this, CREATE_SUSPENDED, &winThreadID);
	if (!hThread)
		printf("_beginthreadex failed at ", __FILE__, __LINE__);
}
Thread::Thread() : runnable(nullptr) {
	hThread = (HANDLE)_beginthreadex(NULL, 0, Thread::startThread,
		(LPVOID)this, CREATE_SUSPENDED, &winThreadID);
	if (!hThread) printf("_beginthreadex failed at ", __FILE__, __LINE__);
}

unsigned WINAPI Thread::startThreadRunnable(LPVOID pVoid) {
	Thread* runnableThread = static_cast<Thread*> (pVoid);
	runnableThread->result = runnableThread->runnable->run();
	runnableThread->setCompleted();
	return reinterpret_cast<unsigned>(runnableThread->result);
}
unsigned WINAPI Thread::startThread(LPVOID pVoid) {
	Thread* aThread = static_cast<Thread*> (pVoid);
	assert(aThread);
	aThread->result = aThread->run();
	aThread->setCompleted();
	return reinterpret_cast<unsigned>(aThread->result);
}
Thread::~Thread() {
	if (winThreadID != GetCurrentThreadId()) {
		DWORD rc = CloseHandle(hThread);
		if (!rc) printf("CloseHandle failed at ", __FILE__, __LINE__);
	}
	// note that the runnable object (if any) is automatically deleted by unqiue_ptr.
}
void Thread::start() {
	assert(hThread != NULL);
	DWORD rc = ResumeThread(hThread);
	// thread was created in suspended state so this starts it running
	if (!rc) printf("ResumeThread failed at ", __FILE__, __LINE__);
}
void* Thread::join() {
	DWORD rc = WaitForSingleObject(
		completionEvent, // handle to event
		INFINITE); // no timeout
	if (!(rc == WAIT_OBJECT_0))
		printf("WaitForSingleObject failed at ", __FILE__, __LINE__);
	return result;
}
void Thread::setCompleted() {
	DWORD rc = SetEvent(completionEvent);
	if (!rc)
		printf("SetEvent failed at ", __FILE__, __LINE__);
}