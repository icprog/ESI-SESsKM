// SCADA_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool InitializeWindowsSockets();
enum fcodes { AI = 0x04, DI = 0x02 };
void makeRequests(DigitalDevice *dd, AnalogInput *ai, char *request);
int main()
{
	if (InitializeWindowsSockets() == false)
	{
		// we won't log anything since it will be logged
		// by InitializeWindowsSockets() function
		return 1;
	}
	Buffer *commandingBuffer = new Buffer("commanding_buffer", 512);
	Buffer *sharedBuffer = new Buffer("shared_buffer", 512);
	Buffer *streamBuffer = new Buffer("stream_buffer", 8000);
	RemoteTelemetryUnit *rtu = Util::parseXMLConfig();

	TCPDriver::getInstance().setIpAddress("127.0.0.1");
	TCPDriver::getInstance().setPort(502);
	int iResult = TCPDriver::getInstance().tcpConnect();
	if (iResult != 0) {
		std::cout << "Error connectiong to the modbus." << std::endl;
		WSACleanup();
		return 0;
	}
	
	ClientHandler *ch = new ClientHandler(commandingBuffer, streamBuffer, 1, "127.0.0.1", "27016", rtu);
	ch->tcpConnect();
	
	std::vector<char *> *vector = new std::vector<char *>();

	char *req = nullptr;
	for (int i = 0; i < rtu->getAnalogInputNum(); i++) {
		req = new char[5];
		makeRequests(nullptr, rtu->getAnalogInputs().at(i), req);
		req[3] = 0x00;
		req[4] = 0x01;
		vector->push_back(req);
		//delete req;
	}
	DataProcessingEngine *processEngine = new DataProcessingEngine(sharedBuffer,streamBuffer, rtu);

	PollEngine *pollEngine = new PollEngine(vector, sharedBuffer);
//	PollEngine::sendRequests(pollEngine);
	//delete commandingBuffer, commandingBuffer = 0;
	//delete streamBuffer, streamBuffer = 0;
	//delete ch, ch = 0;
	
	//double value = rtu->getAnalogInputs().at(0)->getValue();
	//std::cout << "Value is: " << value << std::endl;
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

void makeRequests(DigitalDevice *dd, AnalogInput *ai, char *request) {
	if(dd == nullptr){
		request[0] = AI;
		*((short*)(request + 1)) = htons(ai->getAddress());
	}
	else {
		request[0] = DI;
		*((short*)(request + 1)) = htons( dd->getInAddresses()[0]);
	}


}