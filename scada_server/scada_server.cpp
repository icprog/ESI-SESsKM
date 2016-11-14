
// scada_server.cpp : Defines the entry point for the console application.
//
/*
#include "stdafx.h"
#include "EngineeringUnit.h"
#include "AnalogInput.h"
#include "RTU.h"
int main()
{
	EngineeringUnit *eu = new EngineeringUnit(1, "centimetar", "cm");
	AnalogInput *ai = new AnalogInput("a1", 123, 50, 500, 350, 2016, 4000, 2500, 10, 19, "21.10.2015.", *eu);
	std::vector<AnalogInput> inputs;
	inputs.push_back(*ai);
	RTU *rtu = new RTU(1, "MODBUS", "TCP", "192.168.101.77", 5000, 1, 0, 0, 0, &inputs, nullptr, nullptr);
	delete eu;
	delete ai;
	delete rtu;
    return 0;
}

*/

// scada_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "Thread.h"
#pragma comment(lib, "Ws2_32.lib")
/*
class simpleRunnable : public Runnable {
public:
	simpleRunnable(int ID) : myID(ID) {}
	virtual void* run() {
		std::cout << "Thread " << myID << "is running" << std::endl;
		return reinterpret_cast<void*>(myID);
	}
private:
	int myID;
};
class simpleThread : public Thread {
public:
	simpleThread(int ID) : myID(ID) {}
	virtual void* run() {
		std::cout << "Thread " << myID << "is running" << std::endl;
		return reinterpret_cast<void*>(myID);
	}
private:
	int myID;
};
*/
#include "IServerMediator.h"
#include "ServerMediator.h"
#include "IComponent.h"
#include "PollEngine.h"
#include <vector>
bool InitializeWindowsSockets();
int main() {
	/*
	std::unique_ptr<Runnable> r(new simpleRunnable(1));
	std::unique_ptr<Thread> thread1(new Thread(std::move(r)));
	thread1->start();
	std::unique_ptr<simpleThread> thread2(new simpleThread(2));
	thread2->start();
	simpleThread thread3(3);
	thread3.start();
	// thread1 and thread2 are created on the heap; thread3 is created on the stack
	// wait for the threads to finish
	int result1 = reinterpret_cast<int>(thread1->join());
	int result2 = reinterpret_cast<int>(thread2->join());
	int result3 = reinterpret_cast<int>(thread3.join());
	std::cout << result1 << ' ' << result2 << ' ' << result3 << std::endl;
	return 0;
	*/
	if (InitializeWindowsSockets() == false)
	{
		// we won't log anything since it will be logged
		// by InitializeWindowsSockets() function
		return 1;
	}

	Util::readFromFile(); //ucitavanje konf. fajla i punjenje modela

	IServerMediator *med = new ServerMediator();

	SOCKET sock = INVALID_SOCKET;


	char tuid[2];
	char puid[2];
	char lenp[2];
	char uid;
	tuid[0] = 0x01;
	tuid[1] = 0x00;
	puid[0] = 0x00;
	puid[1] = 0x00;
	lenp[0] = 0x06;
	lenp[1] = 0x00;
	uid = 0x00;

	TCPHeader *tcpHeader = new TCPHeader(tuid, puid, lenp, uid);

	char f = 0x06;
	char sa[2];
	char val[2];
	sa[0] = 0x01;
	sa[1] = 0x00;
	val[0] = 0x05;
	val[1] = 0x00;
	PDU *pdu = new PDU(f, sa, val);
	Request *req = new Request(tcpHeader, pdu);
	std::vector<Request*> vec;
	vec.push_back(req);
	CRITICAL_SECTION cs;
	InitializeCriticalSection(&cs);
	Buffer *buffer = new Buffer("red1", 512, &cs);
	//buffer->createBuffer("red1", 512, &cs);
	char response[600];

	std::unique_ptr<PollEngine> pollEngineThread(new PollEngine(1, buffer, &vec, 1, false, "127.0.0.1", 502, &sock));
	pollEngineThread->start();
	int result1 = reinterpret_cast<int>(pollEngineThread->join());
	// the destructors for thread1 and thread2 will automatically delete the
	// pointed-at thread objects
	std::cout << result1 << std::endl;
	Sleep(INFINITE);
	return 0;
}
bool InitializeWindowsSockets()
{
	WSADATA wsaData;
	// Initialize windows sockets library for this process
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup failed with error: %d\n", WSAGetLastError());
		return false;
	}
	return true;
}


