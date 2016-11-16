
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
#include "AnalogInput.h"
#include "DataProcessingEngine.h"
#include "RTU.h"
#include <vector>
#include "ClientHandler.h"
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

	RTU *rtu = Util::readFromFile();
	//RTU *rtu = new RTU();
	//Util::readFromFile(rtu); //ucitavanje konf. fajla i punjenje modela

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

	/////request 1 zadata temp.
	char f1 = 0x04;
	char sa1[2];
	char val1[2];
	sa1[0] = 0x00;
	sa1[1] = 0x01;
	val1[0] = 0x00;
	val1[1] = 0x01;
	/////
	/////request 2 spoljasnja temp.
	char f2 = 0x04;
	char sa2[2];
	char val2[2];
	sa2[0] = 0x00;
	sa2[1] = 0x02;
	val2[0] = 0x00;
	val2[1] = 0x01;
	/////
	/////request 3 unutrasnja temp.
	char f3 = 0x04;
	char sa3[2];
	char val3[2];
	sa3[0] = 0x00;
	sa3[1] = 0x03;
	val3[0] = 0x00;
	val3[1] = 0x01;
	/////
	/////request 4 digitalni ulaz, stanje grejaca
	char f4 = 0x02;
	char sa4[2];
	char val4[2];
	sa4[0] = 0x00;
	sa4[1] = 0x04;
	val4[0] = 0x00;
	val4[1] = 0x01;
	/////

	PDU *pdu1 = new PDU(f1, sa1, val1);
	Request *req1 = new Request(tcpHeader, pdu1);
	PDU *pdu2 = new PDU(f2, sa2, val2);
	Request *req2 = new Request(tcpHeader, pdu2);
	PDU *pdu3 = new PDU(f3, sa3, val3);
	Request *req3 = new Request(tcpHeader, pdu3);
	PDU *pdu4 = new PDU(f4, sa4, val4);
	Request *req4 = new Request(tcpHeader, pdu4);
	std::vector<Request*> vec;
	vec.push_back(req1);
	vec.push_back(req2);
	vec.push_back(req3);
	vec.push_back(req4);

	CRITICAL_SECTION cs;
	InitializeCriticalSection(&cs);
	Buffer *buffer = new Buffer("red1", 512, &cs);
	//buffer->createBuffer("red1", 512, &cs);
	char response[600];
	/*
	std::unique_ptr<PollEngine> pollEngineThread(new PollEngine(1, buffer, &vec, 1, false, "127.0.0.1", 502, &sock));
	pollEngineThread->start();
	int result1 = reinterpret_cast<int>(pollEngineThread->join());

	std::unique_ptr<DataProcessing> dataProcessingThread(new DataProcessing(2, buffer, rtu));
	dataProcessingThread->start();
	int result2 = reinterpret_cast<int>(dataProcessingThread->join());
	*/

	char *message = "Ovo je poruka!";
	buffer->push(message, 1);

	SOCKET ls = INVALID_SOCKET, as = INVALID_SOCKET;
	std::unique_ptr<ClientHandler> pollEngineThread(new ClientHandler(1, 1, false, "127.0.0.1", 27016, &ls, &as, buffer));
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


