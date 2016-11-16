#include "stdafx.h"
#include "DataProcessingEngine.h"
#include "AnalogInput.h"
#include "AnalogOutput.h"
#include "RTU.h"
#include <bitset>
using namespace std;


void DataProcessing::dataProcessingEngine(Buffer * recvBuf, vector<int> *addresses, RTU * rtu)
{
	
	//get first address only for debug purpose
	//TODO
	//interate with for loop through all addressees
	//int address = addresses->at(0);
	
	while (recvBuf->getPopIdx() != recvBuf->getPushIdx())
	{
		for (int i = 0; i < addresses->size(); i++) {
			int address = addresses->at(i);

			char dataBuf[512];
			memset(dataBuf, 0, 512);
			recvBuf->pop(dataBuf, 0);

			//preuzimanje zaglavlja i function koda iz bufera
			//char *data = recvBuf->getData();
			short transId = ntohs(*((short*)dataBuf)); //ntohs
			short protID = ntohs(*((short*)(dataBuf + 2))); //ntohs
			short length = ntohs(*((short*)(dataBuf + 4))); //ntohs
			char unitID = *((char*)(dataBuf + 6));
			char fCode = *((char*)(dataBuf + 7));


			if (fCode == 1) {  //citanje digitalnih izlaza
				char byteCount = *((char*)(dataBuf + 8));
				char outputValue = *((char*)(dataBuf + 9));
				cout << "Vrednost je: " << outputValue << endl;
				//da li je potrebno upisati u rtdb??
				//upisi u digitalni izlaz
				vector<DigitalDevice> digitalDevices = rtu->getDigitalDevices();
				for (vector<DigitalDevice>::iterator it = digitalDevices.begin(); it != digitalDevices.end(); ++it) {
					if (it->getOutAddress1() == address || it->getOutAddress2() == address) {
						//it->setState(outputValue);
						it->setStatus(1); //status 1 je ok
					}
				}
				/*DigitalDevice *dd = rtu->digitalDevices[0].data();
				dd->setState(outputValue); // stavi char u state
				dd->setStatus(1); //status 1 je ok
				*/
			}
			else if (fCode == 2) { //citanje digitalnih ulaza
				char byteCount = *((char*)(dataBuf + 8));
				char outputValue = *((char*)(dataBuf + 9));
				cout << "Vrednost je: " << outputValue << endl;
				//upisuje se u rtdb, dig.ulaz
				vector<DigitalDevice> digitalDevices = rtu->getDigitalDevices();
				for (vector<DigitalDevice>::iterator it = digitalDevices.begin(); it != digitalDevices.end(); ++it) {
					if (it->getInAddress1() == address || it->getInAddress2() == address) {
						//it->setState(outputValue);
						it->setStatus(1); //status 1 je ok
					}
				}

				/*DigitalDevice *dd = rtu->digitalDevices[0].data();
				dd->setState(outputValue); //stavi char u state
				dd->setStatus(1); // status 1 je ok
				*/
			}
			else if (fCode == 3) { //citanje analognih izlaza
				char numEnt = *((char*)(dataBuf + 8));
				short inpVal = ntohs(*((short*)(dataBuf + 9))); //ne znam da li treba ntohs
				//koji analogni izlaz upisujem??
				vector<AnalogOutput> analogOutputs = rtu->getAnalogOutputs();

				for (vector<AnalogOutput>::iterator it = analogOutputs.begin(); it != analogOutputs.end(); ++it) {
					if (it->getAddress() == address) {
						it->setRaw(inpVal);

						if (inpVal < it->getRawMax() || inpVal > it->getRawMin()) {
							//formula za konverziju iz analog u egu
							//rtuIn.EGU = (rtuIn.Raw * rtuIn.EGUMax)/rtuIn.RawMax;
							//rtuIn->setEGU((rtuIn->getRaw() * rtuIn->getEGUMax()) / rtuIn->getEGUMin()); //proveri formulu
							it->setEGU(((it->getEGUMax() - it->getEGUMin()) / (it->getRawMax() - it->getRawMin()))*(it->getRaw() - it->getRawMin()) + it->getEGUMin());
							it->setStatus(1); //status 1 je ok, postavi status u rtuIn na ok
						}
						else {
							it->setStatus(0); //status 0 je err, postavi status u rtuIn na err
						}
						break;
					}
				}

				/*rtuOut->setRaw(inpVal);

				if (inpVal < rtuOut->getRawMax() || inpVal > rtuOut->getRawMin()) {
					//formula za konverziju iz analog u egu
					//rtuOut->setEGU((rtuOut->getRaw() * rtuOut->getEGUMax()) / rtuOut->getEGUMin()); //proveri formulu
					rtuOut->setEGU(((rtuOut->getEGUMax() - rtuOut->getEGUMin())/(rtuOut->getRawMax() - rtuOut->getRawMin()))*(rtuOut->getRaw()-rtuOut->getRawMin())+rtuOut->getEGUMin());
					rtuOut->setStatus(1); //status 1 je ok
				}
				else {
					rtuOut->setStatus(0); //status 0 je err
				}*/

			}
			else if (fCode == 4) {  //un.,sp. temp,citanje vrednosti iz registara
				//00 01 00 00 05 01 04 00 10 00
				char numEnt = *((char*)(dataBuf + 8));
				short inpVal = ntohs(*((short*)(dataBuf + 9))); //ne znam da li treba ntohs
				//koji analogni uzal upisujem??
				vector<AnalogInput> analogInputs = rtu->getAnalogInputs();

				for (vector<AnalogInput>::iterator it = analogInputs.begin(); it != analogInputs.end(); ++it) {
					if (it->getAddress() == address) {
						it->setRaw(inpVal);

						if (inpVal < it->getRawMax() || inpVal > it->getRawMin()) {
							//formula za konverziju iz analog u egu
							//rtuIn.EGU = (rtuIn.Raw * rtuIn.EGUMax)/rtuIn.RawMax;
							//rtuIn->setEGU((rtuIn->getRaw() * rtuIn->getEGUMax()) / rtuIn->getEGUMin()); //proveri formulu
							it->setEGU(((it->getEGUMax() - it->getEGUMin()) / (it->getRawMax() - it->getRawMin()))*(it->getRaw() - it->getRawMin()) + it->getEGUMin());
							it->setStatus(1); //status 1 je ok, postavi status u rtuIn na ok
						}
						else {
							it->setStatus(0); //status 0 je err, postavi status u rtuIn na err
						}
						break;
					}
				}
				//AnalogInput rtuIn = rtu->getAnalogInputs().at(0);
				/*rtuIn.setRaw(inpVal); //potrebno je na rtu input[0].Raw postaviti inpVal

				if (inpVal < rtuIn.getRawMax() || inpVal > rtuIn.getRawMin()) {
					//formula za konverziju iz analog u egu
					//rtuIn.EGU = (rtuIn.Raw * rtuIn.EGUMax)/rtuIn.RawMax;
					//rtuIn->setEGU((rtuIn->getRaw() * rtuIn->getEGUMax()) / rtuIn->getEGUMin()); //proveri formulu
					rtuIn.setEGU(((rtuIn.getEGUMax() - rtuIn.getEGUMin()) / (rtuIn.getRawMax() - rtuIn.getRawMin()))*(rtuIn.getRaw() - rtuIn.getRawMin()) + rtuIn.getEGUMin());
					rtuIn.setStatus(1); //status 1 je ok, postavi status u rtuIn na ok
				}
				else {
					rtuIn.setStatus(0); //status 0 je err, postavi status u rtuIn na err
				}
				*/

			}

			else if (fCode == 5) { // pisanje dig.izlaza, nista se ne upisuje
				//char byteCount = *((char*)(recvBuf + 8));
				//char result = *((char*)(recvBuf + 9));
				short outAddress = *((short*)(dataBuf + 4));
				short outputValue = *((short*)(dataBuf + 5));

			}
			else if (fCode == 6) { //pisanje analognih izlaza, nista se ne upisuje
				//int inp = (int)(*((char*)(recvBuf + 11)));
				//std::cout << "Upisuje se vrednost" << std::endl;
				short registerAddress = *((short*)(dataBuf + 4));
				short registerValue = *((short*)(dataBuf + 5));
			}
			else {
				cout << "\nNepoznat function code" << endl;
				//ako je nepoznat fun code mozda bi mogao da se napravi alarm
			}

		}
		Sleep(200); //spava 200 i onda pokusa ponovo
	}
}

void * DataProcessing::run()
{
	this->dataProcessingEngine(this->myBuffer, this->addresses, this->rtu);
	return reinterpret_cast<void*>(threadId);
}
