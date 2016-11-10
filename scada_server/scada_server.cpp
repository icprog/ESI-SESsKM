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

/*
#include "stdafx.h"
#include "Buffer.h"
#include <windows.h>
using namespace std;

int main()
{
	
	/////////////////////////
	char *data = new char[25];
	memset(data, 0, 25);
	data[0] = 25;
	char *poruka = "ovo je poruka!";
	//*((short *)data + 2) = 20;
	memcpy((int *)data + 1, poruka, 14);
	*((short *)data + 2) = 25;
	/////////////////////////


	/////////////////////////
	char *data2 = new char[5];
	memset(data2, 0, 5);
	data2[0] = 5;
	poruka = "nije";
	memcpy((int *)data2 + 1, poruka, 4);
	*((short *)data2 + 2) = 5;
	/////////////////////////

	/////////////////////////
	char *data3 = new char[15];
	memset(data3, 0, 15);
	data3[0] = 15;
	poruka = "mozda ovo";
	memcpy((int *)data3 + 1, poruka, 9);
	*((short *)data3 + 2) = 15;
	////////////////////////

	char * name = "buf1";

	CRITICAL_SECTION cs;

	Buffer *myBuffer = new Buffer(name,35,&cs);

	myBuffer->push(data);
	myBuffer->push(data2);
	myBuffer->pop(data);
	myBuffer->push(data3);
	myBuffer->push(data);

	//myBuffer->expand();


	return 0;
}
*/

// scada_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Thread.h"
#include "Buffer.h"
#include "AnalogInput.h"


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

class dataProcesing : public Thread {
public:
	dataProcesing(Buffer* buffRecv, char* buffData) : myBuffer(buffRecv), myData(buffData) {}
	virtual void* run() {
		//preuzimanje zaglavlja i function koda iz bufera
		short transId = /*ntohs*/(*((short*)myBuffer));
		short protID = /*ntohs*/(*((short*)(myBuffer + 2)));
		short length = /*ntohs*/(*((short*)(myBuffer + 4)));
		char unitID = *((char*)(myBuffer + 6));
		char fCode = *((char*)(myBuffer + 7));
		
		//obradi poruku u zavisnosti od function koda
		if (fCode == 1 || fCode == 2) {
			char outputValue = *((char*)(myBuffer + 9));
			std::cout << "Heater is " << outputValue;

		}
		else if (fCode == 5) {
			char byteCount = *((char*)(myBuffer + 8));
			char result = *((char*)(myBuffer + 9));
		}
		else if (fCode == 3 || fCode == 4) { //citanje vrednosti iz registara
			char numEnt = *((char*)(myBuffer + 8));
			short inpVal = /*ntohs(*/*((short*)(myBuffer + 9))/*)*/; //ne znam da li treba ntohs
			int temp = int(numEnt) / 2;

			////////////////////////
			//ove podatke je potrebno iscitati iz modela
			int RawMin = 0;
			int RawMax = 4000;
			int Raw = 0;
			int EGUMax = 0;
			int EGUMin = 0;
			int EGU = 0;	
			////////////////////////

			if (inpVal < RawMax || inpVal > RawMin) { //provera da li je taj input u opsegu
				//potrebno je izvrsiti konverziju u EGU i staviti u model
				EGU = (Raw - RawMin) / (RawMax - RawMin)*(EGUMax - EGUMin) + EGUMin;
				//ovaj EGU je potrebno uneti u model
				std::cout << "Ok" << std::endl;
				std::cout << "Vrednost EGU je: " << EGU << std::endl;
				
			}
			else {
				std::cout << "ERROR" << std::endl;
				//treba staviti u status error
			}
			
		}
		else if (fCode == 6) { //pisanje u registar
			int inp = (int)(*((char*)(myBuffer + 11)));
			std::cout << "Upisuje se vrednost" << std::endl;
		}
		

		//skinuti podatak iz bafera
		myBuffer->pop(myData);
		return reinterpret_cast<void*>(myBuffer);
	}
private:
	Buffer* myBuffer;
	char* myData;
};


/*class readFileTread : public Thread {
public:
	readFileTread(int ID) : myID(ID) {}
	virtual void* run() {
		FILE* file = fopen("C:\\Users\\ra64-2012\\Desktop\\blok2novi\\ESI-SESsKM\\Configuration.txt", "r");
		char buffer[2048];

		while (fgets(buffer, 2048, file))
		{
			cout << buffer << '\n';
		}

		return reinterpret_cast<void*>(myID);
	}
private:
	int myID;
};
*/

int main() {
	char *name = "bufer1";
//	CRITICAL_SECTION *cs;
	//char myBuffer[5];
	//myBuffer[0] = 0x01;
	//myBuffer[1] = 0x00;
	Buffer* myBuffer = new Buffer();
	char * data = nullptr;

	std::unique_ptr<Runnable> r(new simpleRunnable(1));
	std::unique_ptr<Thread> thread1(new Thread(std::move(r)));
	thread1->start();
	std::unique_ptr<simpleThread> thread2(new simpleThread(2));
	thread2->start();
	simpleThread thread3(3);
	thread3.start();
	dataProcesing thread4(myBuffer, data);
	thread4.start();
	//readFileTread thread5(5);
	//thread5.start();
	// thread1 and thread2 are created on the heap; thread3 is created on the stack
	// wait for the threads to finish
	int result1 = reinterpret_cast<int>(thread1->join());
	int result2 = reinterpret_cast<int>(thread2->join());
	int result3 = reinterpret_cast<int>(thread3.join());
	int result4 = reinterpret_cast<int>(thread4.join());
	//int result5 = reinterpret_cast<int>(thread5.join());

	std::cout << result1 << ' ' << result2 << ' ' << result3 << ' ' << result4 << std::endl;
	return 0;
	// the destructors for thread1 and thread2 will automatically delete the
	// pointed-at thread objects
}
