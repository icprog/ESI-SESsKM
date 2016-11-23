// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Util/Util.h"
#include "../DataProcessingEngine/DataProcessingEngine.h"
#include <iostream>
#include <conio.h> 
#include <windows.h>
using namespace std;

void gotoxy(int x, int y);
void setcolor(WORD color);
void clrscr();


int main()
{
	int x, y, i; char name[10];

	setcolor(10);
	cout << "Welcome\n";

	setcolor(15);
	cout << "\nEnter your name  ";
	//gets(name);
	cin >> name;

	i = 0;
	x = 22;
	y = 12;

	while (1) {

		// counter for text color
		i++; if (i>15) i = 1;

		// print colored text
		setcolor(i);
		gotoxy(x, y);
		cout << "Welcome  " << name;
		Sleep(100);


		// Print black text to simulate blink
		setcolor(0);
		gotoxy(x, y);
		cout << "                        ";
		Sleep(100);

		cout << "\nASFSAFSA  " <<endl;

	}

	setcolor(7);
	gotoxy(1, 24);
	/*RemoteTelemetryUnit *rtu = Util::parseXMLConfig();
	//punimo bafer sa responsom i requestom zbog testiranja dataProcesinga
	//4 bajta duzina cele poruke, pa 4 bajta duzina responsea, pa response pa request
	char reqres1[31];
	//4 bajta duzina cele poruke
	reqres1[0] = 0x1F;
	reqres1[1] = 0x00;
	reqres1[2] = 0x00;
	reqres1[3] = 0x00;
	//4 bajta duzina responsa
	reqres1[4] = 0x0B;
	reqres1[5] = 0x00;
	reqres1[6] = 0x00;
	reqres1[7] = 0x00;
	//response header
	reqres1[8] = 0x00; //trans. id
	reqres1[9] = 0x01;
	reqres1[10] = 0x00; //prot. id
	reqres1[11] = 0x01;
	reqres1[12] = 0x00; //length
	reqres1[13] = 0x05;
	reqres1[14] = 0x01; //unit  id
						//response
	reqres1[15] = 0x04;   //func.code
	reqres1[16] = 0x01;   //byte count
	reqres1[17] = 0x01;   //reg.value
	reqres1[18] = 0x00;
	//request header
	reqres1[19] = 0x00; //trans. id
	reqres1[20] = 0x01;
	reqres1[21] = 0x00; //prot. id
	reqres1[22] = 0x01;
	reqres1[23] = 0x00; //length
	reqres1[24] = 0x05;
	reqres1[25] = 0x01; //unit  id
						//request
	reqres1[26] = 0x04;   //func.code
	reqres1[27] = 0x01;   //starting address
	reqres1[28] = 0x00;
	reqres1[29] = 0x00;	  //quan.od coils
	reqres1[30] = 0x01;

	Buffer *sharedBuffer = new Buffer("buf1", 512);
	sharedBuffer->push(reqres1, 31);

	DataProcessingEngine *dp = new DataProcessingEngine(sharedBuffer, rtu);
	//dp->process(sharedBuffer, rtu);
	DataProcessingEngine::process(dp);
	double value = rtu->getAnalogInputs().at(0)->getValue();
	std::cout<<std::endl;
	std::cout << "Value is: " << value << std::endl;
	*/
	return 0;
}
void setcolor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;
}



void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}




void clrscr()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
	return;
}