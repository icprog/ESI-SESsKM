#include "stdafx.h"
#include "DataProcessingEngine.h"
#include "AnalogInput.h"
#include "AnalogOutput.h"
#include "RTU.h"
#include <bitset>
using namespace std;


void DataProcessing::dataProcessingEngine(Buffer * recvBuf, /*char * data,*/ RTU * rtu)
{
	//preuzimanje zaglavlja i function koda iz bufera
	short transId = (*((short*)recvBuf)); //ntohs
	short protID = (*((short*)(recvBuf + 2))); //ntohs
	short length = (*((short*)(recvBuf + 4))); //ntohs
	char unitID = *((char*)(recvBuf + 6));
	char fCode = *((char*)(recvBuf + 7));


	if (fCode == 1 ) {  //citanje digitalnih izlaza
		char outputValue = *((char*)(recvBuf + 9));
		cout << "Vrednost je: " << outputValue << endl;
		//da li je potrebno upisati u rtdb??
		//upisi u digitalni izlaz
		DigitalDevice *dd = rtu->digitalDevices[0].data();
		dd->setState(outputValue); // stavi char u state
		dd->setStatus(1); //status 1 je ok
	}
	else if (fCode == 2) { //citanje digitalnih ulaza
		char outputValue = *((char*)(recvBuf + 9));
		cout << "Vrednost je: " << outputValue << endl;
		//upisuje se u rtdb, dig.ulaz
		DigitalDevice *dd = rtu->digitalDevices[0].data();
		dd->setState(outputValue); //stavi char u state
		dd->setStatus(1); // status 1 je ok
	}
	else if (fCode == 3) { //citanje analognih izlaza
		char numEnt = *((char*)(recvBuf + 8));
		short inpVal = ntohs(*((short*)(recvBuf + 9))); //ne znam da li treba ntohs
		int temp = int(numEnt) / 2;

		AnalogOutput *rtuOut = rtu->analogOutputs[0].data();
		rtuOut->setRaw(inpVal);

		if (inpVal < rtuOut->getRawMax() || inpVal > rtuOut->getRawMin()) {
			//formula za konverziju iz analog u egu
			//rtuOut->setEGU((rtuOut->getRaw() * rtuOut->getEGUMax()) / rtuOut->getEGUMin()); //proveri formulu
			rtuOut->setEGU(((rtuOut->getEGUMax() - rtuOut->getEGUMin())/(rtuOut->getRawMax() - rtuOut->getRawMin()))*(rtuOut->getRaw()-rtuOut->getRawMin())+rtuOut->getEGUMin());
			rtuOut->setStatus(1); //status 1 je ok
		}
		else {
			rtuOut->setStatus(0); //status 0 je err
		}

	}
	else if (fCode == 4) {  //un.,sp. temp,citanje vrednosti iz registara
		char numEnt = *((char*)(recvBuf + 8));
		short inpVal = ntohs(*((short*)(recvBuf + 9))); //ne znam da li treba ntohs
		int temp = int(numEnt) / 2;

		AnalogInput *rtuIn = rtu->analogInputs[0].data();
		rtuIn->setRaw(inpVal); //potrebno je na rtu input[0].Raw postaviti inpVal

		if (inpVal < rtuIn->getRawMax() || inpVal > rtuIn->getRawMin()) {
			//formula za konverziju iz analog u egu
			//rtuIn.EGU = (rtuIn.Raw * rtuIn.EGUMax)/rtuIn.RawMax;
			//rtuIn->setEGU((rtuIn->getRaw() * rtuIn->getEGUMax()) / rtuIn->getEGUMin()); //proveri formulu
			rtuIn->setEGU(((rtuIn->getEGUMax() - rtuIn->getEGUMin()) / (rtuIn->getRawMax() - rtuIn->getRawMin()))*(rtuIn->getRaw() - rtuIn->getRawMin()) + rtuIn->getEGUMin());
			rtuIn->setStatus(1); //status 1 je ok, postavi status u rtuIn na ok
		}
		else {
			rtuIn->setStatus(0); //status 0 je err, postavi status u rtuIn na err
		}

	}

	else if (fCode == 5) { // pisanje dig.izlaza
		char byteCount = *((char*)(recvBuf + 8));
		char result = *((char*)(recvBuf + 9));
	}
	else if (fCode == 6) { //pisanje analognih izlaza
		int inp = (int)(*((char*)(recvBuf + 11)));
		std::cout << "Upisuje se vrednost" << std::endl;

	}
	else {
		cout << "\nNepoznat function code" << endl;
	}


}