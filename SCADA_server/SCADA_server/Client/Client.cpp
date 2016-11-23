// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <thread>
#include "../Util/Util.h"
#include "../Model/AnalogInput.h"
#include "../Model/RemoteTelemetryUnit.h"
#include "../Util/Buffer.h"
#include "../Util/NonBlockingSocket.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 27016

bool InitializeWindowsSockets();
int makeConnect(SOCKET *connectSocket);
void receiveMessage(SOCKET *accSock, RemoteTelemetryUnit *rtu);
void parseMessage(char *dataBuf, RemoteTelemetryUnit *rtu1, SOCKET *connectSocket);
void printValues(RemoteTelemetryUnit *rtu);
void parseAlarm(char * dataBuf, RemoteTelemetryUnit *rtu, SOCKET *connectSocket);

void setColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

int main()
{
	// socket used to communicate with server
	SOCKET connectSocket = INVALID_SOCKET;
	// variable used to store function return value
	int iResult;
	int connected = -1;
	connected = makeConnect(&connectSocket);
	if (connected == 0) {
		std::cout << "Client connected." << std::endl;
	}

	RemoteTelemetryUnit *rtu1 = Util::parseXMLConfig();

	receiveMessage(&connectSocket, rtu1);
    return 0;
}

void parseMessage(char * dataBuf, RemoteTelemetryUnit *rtu, SOCKET *connectSocket) {

	int messageSize = *(int*)dataBuf;

	int oznaka = *(int*)(dataBuf + 4);
	short address = *(int*)(dataBuf + 8);
	bool changeValue = false; //za ispis
	
	if (oznaka == 1) { //analog input
		double vrednost = *(double*)(dataBuf + 10);
		
		std::vector<AnalogInput*> ai = rtu->getAnalogInputs();
		for (int i = 0; i < ai.size(); i++) {
			if (ai.at(i)->getAddress() == address)
			{
				if (ai.at(i)->getValue() != vrednost) {
					ai.at(i)->setValue(vrednost);
					changeValue = true;
				}
			}
		}
	}
	else if (oznaka == 2) { //analog output
		double vrednost = *(double*)(dataBuf + 10);

		std::vector<AnalogOutput*> ao = rtu->getAnalogOutputs();
		for (int i = 0; i < ao.size(); i++) {
			if (ao.at(i)->getAddress() == address)
			{
				if (ao.at(i)->getValue() != vrednost) {
					ao.at(i)->setValue(vrednost);
					changeValue = true;
				}
			}
		}
	}
	else if (oznaka == 3) { //digital input
		int vrednost = *(int*)(dataBuf + 10);
	
		std::vector<DigitalDevice*> di = rtu->getDigitalDevices();
		for (int i = 0; i < di.size(); i++) {
			short *inAddresses = di.at(i)->getInAddresses();
			if (inAddresses[0] == address || inAddresses[1] == address) {
				if (di.at(i)->getState() != vrednost) {
					if (vrednost == 0) {
						di.at(i)->setState(DigitalDevice::ON);
						changeValue = true;
					}
					if (vrednost == 1) {
						di.at(i)->setState(DigitalDevice::OFF);
						changeValue = true;
					}
					
				}
			}
		}
	}
	else if (oznaka == 4) { //digital output
		int vrednost = *(int*)(dataBuf + 10);

		std::vector<DigitalDevice*> dout = rtu->getDigitalDevices();
		for (int i = 0; i < dout.size(); i++) {
			short *outAddresses = dout.at(i)->getOutAddresses();
			if (outAddresses[0] == address || outAddresses[1] == address) {
				if (dout.at(i)->getState() != vrednost) {
					if (vrednost == 0) {
						dout.at(i)->setState(DigitalDevice::ON);
						changeValue = true;
					}
					if (vrednost == 1) {
						dout.at(i)->setState(DigitalDevice::OFF);
						changeValue = true;
					}
				}
			}
		}
	}
	
	else {
		std::cout << "Nepoznata oznaka" << std::endl;
	}

	if (changeValue) {
		printValues(rtu);
	}
}

void parseAlarm(char * dataBuf, RemoteTelemetryUnit *rtu, SOCKET *connectSocket) {
	int messageSize = *(int*)dataBuf;

	int oznaka = *(int*)(dataBuf + 4);
	short address = *(int*)(dataBuf + 8);
	bool changeValue = false; //za ispis

	if (oznaka == 5) { //alarm
		char *messageToSend = new char[6];
		*(int*)messageToSend = 6;
		messageToSend[4] = *(char*)(dataBuf + 8); //adresa
		messageToSend[5] = *(char*)(dataBuf + 9); //adresa
		int alarmMessageSize = *(int*)(dataBuf + 10);

		char *alarmMessage = new char;
		for (int i = 0; i < alarmMessageSize; i++) {
			alarmMessage[i] = *(char*)(dataBuf + 14 + i);
		}
		bool confirmedBool = false;
		while (!confirmedBool) {
			setColor(12); //postavi boju na crvenu
			std::cout << alarmMessage << std::endl;

			//setColor(7); //postavi boju na belu
			int confirmed = 0;
			do {
				std::cout << "You must confirm alarm! Enter 1 to confirm" << std::endl;
				scanf("%d", &confirmed);
			} while (confirmed != 1);
			confirmedBool = true;
		}
		std::cout << "Potvdio si alarm" << std::endl;
		//treba sada poslati 2 bajta tj. adresu
		// Send an prepared message with null terminator included
		//NonBlockingSocket *nbs = new NonBlockingSocket();
		//nbs->SEND(connectSocket, addressAlarm, 2);
		int iResult;
		iResult = send(*connectSocket, messageToSend, 6, 0);

		if (iResult == SOCKET_ERROR)
		{
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(*connectSocket);
			WSACleanup();
			//return 1;
		}
		printf("Bytes Sent: %ld\n", iResult);
	}
	else {
		std::cout << "Nepoznata oznaka" << std::endl;
	}
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

int makeConnect(SOCKET *connectSocket) {
	if (InitializeWindowsSockets() == false)
	{
		// we won't log anything since it will be logged
		// by InitializeWindowsSockets() function
		return 1;
	}

	// create a socket
	*connectSocket = socket(AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP);

	if (*connectSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// create and initialize address structure
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress.sin_port = htons(DEFAULT_PORT);
	// connect to server specified in serverAddress and socket connectSocket
	if (connect(*connectSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		printf("Unable to connect to server.\n");
		closesocket(*connectSocket);
		WSACleanup();
	}
	return 0;
}


void receiveMessage(SOCKET *accSock, RemoteTelemetryUnit *rtu) {
	int iResult = -1;
	char *response = nullptr;
	NonBlockingSocket *nbs = new NonBlockingSocket();
	do {
		response = new char[1024];
		
		iResult = nbs->RECEIVE(accSock, response, 4);
		//std::cout << iResult << std::endl;
		if (iResult > 0)
		{
			int size = *(int *)response;
			if (size == 18) {
				parseMessage(response, rtu, accSock);
			}
			else {
				parseAlarm(response, rtu, accSock);
			}
		}
		else if (iResult == 0)
		{
			// connection was closed gracefully
			printf("Connection with server established.\n");
			//closesocket(*acceptedSocket);
			break;
		}
		else
		{
			// there was an error during recv
			printf("recv failed with error: %d\n", WSAGetLastError());
			//closesocket(*acceptedSocket);
			break;
		}
	} while (iResult > 0);
}




void printValues(RemoteTelemetryUnit *rtu) {
	//prodji kroz sve inpute, outpute i dig.device i ipisi ih na konzoli
	system("cls");
	std::cout << "----------------------------------------------------" << std::endl;
	std::vector<AnalogInput*> ai = rtu->getAnalogInputs();
	for (int i = 0; i < ai.size(); i++) {
		std::cout << ai.at(i)->getName() << " : " << ai.at(i)->getValue() << std::endl;
	}

	std::vector<AnalogOutput*> ao = rtu->getAnalogOutputs();
	for (int i = 0; i < ao.size(); i++) {
		std::cout << ao.at(i)->getName() << " : " << ao.at(i)->getValue() << std::endl;
	}

	std::vector<DigitalDevice*> dout = rtu->getDigitalDevices();
	for (int i = 0; i < dout.size(); i++) {
		//11 error, 00 trans, 01 on , 10 off
		/*char state[2];
		state = dout.at(i)->getState();
		if (state[0] == 0 && state[1] == 1) {
		std::cout << dout.at(i)->getName() << " : " << "ON" << std::endl;
		}
		if (state[0] == 1 && state[1] == 0) {
		std::cout << dout.at(i)->getName() << " : " << "OFF" << std::endl;
		}
		if (state[0] == 0 && state[1] == 0) {
		std::cout << dout.at(i)->getName() << " : " << "TRANSIENT" << std::endl;
		}
		if (state[0] == 1 && state[1] == 1) {
		std::cout << dout.at(i)->getName() << " : " << "ERROR" << std::endl;
		}
		*/
	}
	std::cout << "----------------------------------------------------" << std::endl;
}