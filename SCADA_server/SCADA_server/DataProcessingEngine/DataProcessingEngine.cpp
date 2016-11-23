#include "stdafx.h"
#include "DataProcessingEngine.h"

#define BUFFER_SIZE 512

void DataProcessingEngine::process(DataProcessingEngine *that)
{
	std::cout << "Obradjuju se podaci!!!" << std::endl;
	BlockingQueue<char *> *sharedBuffer = that->getSharedBuffer();
	RemoteTelemetryUnit *rtu = that->getRTU();
	int pollCount = 0;
	short command[2];
	while (1) {
		Sleep(1000);
		while (sharedBuffer->size() > 0) {
			//dobijemo velicinu poruke i responsa iz shared buffera
			int messageLength = Util::getSharedMesageSize(sharedBuffer);
			int responseLength = Util::getSharedResponseSize(sharedBuffer);

			//niz u koji smestam poruku koju skinem sa shared buffera
			char *dataBuf = new char[BUFFER_SIZE];
			memset(dataBuf, 0, BUFFER_SIZE);
			dataBuf = sharedBuffer->pop();

			//uzimamo adresu i function code iz poruke
			short address = ntohs(*((short*)(dataBuf + 8 + responseLength + 8))); //8 bajta duzine,  response size ,i onda jos 8 bajta u req    27
			char fCode = *((char*)(dataBuf + 8 + 7)); //dataBuf +4(za duzinu cele poruke) +4(duzina responsa) +7(response header)

			if (fCode == 1) {  //citanje digitalnih izlaza
<<<<<<< HEAD
				/*char outputValue = *((char*)(dataBuf + 17)); //status dig.izlaza
=======
				/*
				char outputValue = *((char*)(dataBuf + 17)); //status dig.izlaza
>>>>>>> a7b92c38eb1e9665270cd45a115db0c00b099d12
				//upisi u digitalni izlaz
				std::vector<DigitalDevice*> digitalDevices = rtu->getDigitalDevices();

				for (int i = 0; i < digitalDevices.size(); i++) {
					DigitalDevice *it = digitalDevices.at(i);
					short *outAddresses = it->getOutAddresses();

					if (outAddresses[0] == address || outAddresses[1] == address) {
						if (outputValue == 0) {
							it->setState(DigitalDevice::ON);
						}
						if (outputValue == 1) {
							it->setState(DigitalDevice::OFF);
						}
					}
<<<<<<< HEAD
				}*/
=======
				}
				*/
>>>>>>> a7b92c38eb1e9665270cd45a115db0c00b099d12
			}
			else if (fCode == 2) { //citanje digitalnih ulaza
				short outputValue =ntohs( *((short*)(dataBuf + 17))); //status dig.izlaza
				//upisi u digitalni ulaz
				std::vector<DigitalDevice*> digitalDevices = rtu->getDigitalDevices();

				for (int i = 0; i < digitalDevices.size(); i++) {
					DigitalDevice *it = digitalDevices.at(i);
					short *inAddresses = it->getInAddresses();
					if (inAddresses[0] == address || inAddresses[1] == address) {

						// izmeni vrednosti stanja
						if (inAddresses[0] == address ) {
							it->setState(command[0], 0);
						}
						else {
							it->setState(command[1], 1);
						}
						
						if (it->getCommandTime() != 0) {                   // da li je komanda zadata? Ako jeste vreme ce biti promenjeno
							time_t now = time(0);
							double seconds = difftime(now, it->getCommandTime());       // da li je proslo petnaest sekundi od izdavanje komande?
							std::cout << "SEKUNDE PROSLE: " << seconds << std::endl;
							bool commandSuccess = false;
							if (it->getState()[0] == it->getCommand()[0] && it->getState()[1] == it->getCommand()[1])
								commandSuccess = true;


							if (seconds <= 15 && commandSuccess) { // komanda je uspesno izvrsena i nije isteklo 15 sekundi
								//it->setCommand(0);
								it->setCommandTime(0);
								it->setStatus(DigitalDevice::FINISHED);
								std::cout << "KOMANDA IZVRSENA!\n" << std::endl;
							}
							else if(seconds > 0) { // prosle je 15 sekundi i komanda se nije izvrsila, ALARM!
								std::cout << "KOMANDA NIJE IZVRSENA! FORMIRAM ALARM!\s\n" << std::endl;
								short lastAddr = 0;
								if(rtu->getAlarms()->size() > 0)
									lastAddr = rtu->getAlarms()->at(rtu->getAlarms()->size()).getAddress();
								std::string message;
								if (it->getCommand()[0] == 0 && it->getCommand()[1] == 1) {
									message = "Grejac se nije ukljucio!";
								}else
									message = "Grejac se nije iskljucio!";
								Alarm *alarm = new Alarm("ALARM", now, lastAddr + 1, message);
								rtu->getAlarms()->push_back(*alarm);
								that->makeAlarm(that, alarm);

								//delete alarm;
							}
						}
						
						that->pushInStreamBuffer(it, nullptr);
						break;
					}
				}
			}
			else if (fCode == 3) { //citanje analognih izlaza
				short inpVal = ntohs(*((short*)(dataBuf + 17)));

				std::vector<AnalogOutput*> analogOutputs = rtu->getAnalogOutputs();

				for (int i = 0; i < analogOutputs.size(); i++) {
					AnalogOutput *it = analogOutputs.at(i);
					if (it->getAddress() == address) {
						it->setRaw(inpVal);

						if (inpVal <= it->getRawMax() || inpVal >= it->getRawMin()) {
							it->setValue((((double)it->getEGUMax() - it->getEGUMin()) / (it->getRawMax() - it->getRawMin()))*(it->getRaw() - it->getRawMin()) + it->getEGUMin());
							it->setStatus(1); //status 1 je ok, postavi status u rtuIn na ok
						}
						else {
							it->setStatus(0); //status 0 je err, postavi status u rtuIn na err
						}
						break;
					}
				}
			}
			else if (fCode == 4) { //un.,sp. temp,citanje an. ulaza

				short inpVal = ntohs(*((short*)(dataBuf + 17)));
				std::vector<AnalogInput*> analogInputs = rtu->getAnalogInputs();
				pollCount++;
				for (int i = 0; i < analogInputs.size(); i++) {
					AnalogInput *it = analogInputs.at(i);
					if (it->getAddress() == address) {
						if (it->getRaw() == inpVal) {
							break;
						}
						it->setRaw(inpVal);

						if (inpVal <= it->getRawMax() || inpVal >= it->getRawMin()) {
							it->setValue((((double)it->getEGUMax() - it->getEGUMin()) / (it->getRawMax() - it->getRawMin()))*(it->getRaw() - it->getRawMin()) + it->getEGUMin());
							it->setStatus(1); //status 1 je ok, postavi status u rtuIn na ok
							std::cout << "Value from DP is: " << it->getValue() << std::endl;
						}
						else {
							it->setStatus(0); //status 0 je err, postavi status u rtuIn na err
						}
						that->pushInStreamBuffer(nullptr, it);
						break;
					}
				}
			}
			else if (fCode == 5) { //pisanje dig.izlaza, nista se ne upisuje
				short outAddress = *((short*)(dataBuf + 4));
				short outputValue = *((short*)(dataBuf + 5));
			}
			else if (fCode == 6) { //pisanje analognih izlaza, nista se ne upisuje
				short registerAddress = *((short*)(dataBuf + 4));
				short registerValue = *((short*)(dataBuf + 5));
			}
			else {
				std::cout << "\nNepoznat function code" << std::endl;
				//ako je nepoznat fun code mozda bi mogao da se napravi alarm
			}

			if (pollCount == 3) { // zavrsen je poll ciklus
				AnalogInput *zadTemp = that->getRTU()->getAnalogInputs().at(0);
				AnalogInput *unutTemp = that->getRTU()->getAnalogInputs().at(1);
				AnalogInput *spoljTemp = that->getRTU()->getAnalogInputs().at(2);
				DigitalDevice *heater = that->getRTU()->getDigitalDevices().at(0);
				if (unutTemp->getValue() > spoljTemp->getValue() && unutTemp->getValue()<=zadTemp->getValue()) {
					if (heater->getStatus() != DigitalDevice::IN_PROGRESS && heater->getState()[0] != 0 && heater->getState()[1]!=1) { //ako nije zadata komanda onda je zadaj
						that->turnHeaterOn(that, heater, command);
					}

				}
				else if (unutTemp->getValue() > zadTemp->getValue()) {
					if (heater->getStatus() != DigitalDevice::IN_PROGRESS&& heater->getState()[0] != 1 && heater->getState()[1] != 0) { //ako nije zadata komanda onda je zadaj
						that->turnHeaterOff(that, heater, command);
					}
				}
				pollCount = 0;
			}

		}
		//std::cout << "Value from DP is: " << rtu->getAnalogInputs().at(0)->getValue() << std::endl;
		
	}
}

void DataProcessingEngine::pushInStreamBuffer(DigitalDevice *dd, AnalogInput *it)
{
	char *stream;
	// 4 duzina cele poruke + 4 oznaka + 2 adresa + 8 vrednost
	stream = new char[18];
	*((int *)stream) = 18;
	if (dd == nullptr) {
		*((int *)stream + 1) = 1;
		*((short *)(stream + 8)) = it->getAddress();
		*((double *)(stream + 10)) = it->getValue();
	}
	else {
		*((int *)stream + 1) = 2;
		*((short *)(stream + 8)) = dd->getInAddresses()[0];
<<<<<<< HEAD
		*((char *)(stream + 10)) = dd->getState()[0];
=======
		*((short *)(stream + 10)) = dd->getState()[0];
		*((short *)(stream + 12)) = dd->getState()[1];
>>>>>>> a7b92c38eb1e9665270cd45a115db0c00b099d12
		*((int *)(stream + 14)) = 0;
	}
	streamBuffer->push(stream);
	//delete stream;
}

void DataProcessingEngine::makeAlarm(DataProcessingEngine * that, Alarm *alarm)
{
	char *stream;
	// 4 duzina cele poruke + 4 oznaka + 2 adresa + 4 duzina poruka + poruka+ 4 confirmed + 4 corrected
	int messageSize = alarm->getMessage().size();
	stream = new char[22+messageSize];
	*((int *)stream) = 22 + messageSize;
	*((int *)stream + 1) = 5;
	*((short *)(stream + 8)) = alarm->getAddress();
	*((int *)(stream + 10)) = messageSize;
	for (int i = 0; i < messageSize; i++) {
		*(stream + 14 + i) = alarm->getMessage().at(i);
	}
	*((int *)(stream + 14 + messageSize)) = alarm->getConfirmed();
	*((int *)(stream + 18 + messageSize)) = alarm->getCorrected();
	alarmBuffer->push(stream);
}

void DataProcessingEngine::turnHeaterOn(DataProcessingEngine * that, DigitalDevice * dd, short* command)
{
	std::cout << "UKLJUCUJEM GREJAC\n" << std::endl;
	char request1[5], request2[5];
	request1[0] = 0x05;
	*((short*)(request1 + 1)) = htons(dd->getOutAddresses()[0]);
	request1[3] = 0x00;
	request1[4] = 0x00;

	request2[0] = 0x05;
	*((short*)(request2 + 1)) = htons(dd->getOutAddresses()[1]);
	request2[3] = 0x00;
	request2[4] = 0x01;

	char *wholeRequest = new char[12];
	TCPDriver::getInstance().createRequest(request1, wholeRequest);
	TCPDriver::getInstance().sendRequest(wholeRequest);
	wholeRequest = new char[12];
	TCPDriver::getInstance().createRequest(request2, wholeRequest);
	TCPDriver::getInstance().sendRequest(wholeRequest);
	short newCommand[2];
	newCommand[0] = 0;
	newCommand[1] = 1;
	dd->setCommand(newCommand);
	dd->setCommandTime(time(0));
	command[0] = 0;
	command[1] = 1;
	Sleep(1000);
}

void DataProcessingEngine::turnHeaterOff(DataProcessingEngine * that, DigitalDevice * dd, short* command)
{
	std::cout << "ISKLJUCUJEM GREJAC!\n" << std::endl;
	char request1[5], request2[5];
	request1[0] = 0x05;
	*((short*)(request1 + 1)) = htons(dd->getOutAddresses()[0]);
	request1[3] = 0x00;
	request1[4] = 0x01;

	request2[0] = 0x05;
	*((short*)(request2 + 1)) = htons(dd->getOutAddresses()[1]);
	request2[3] = 0x00;
	request2[4] = 0x00;

	char *wholeRequest = new char[12];
	TCPDriver::getInstance().createRequest(request1, wholeRequest);
	TCPDriver::getInstance().sendRequest(wholeRequest);
	wholeRequest = new char[12];
	TCPDriver::getInstance().createRequest(request2, wholeRequest);
	TCPDriver::getInstance().sendRequest(wholeRequest);
	short newCommand[2];
	newCommand[0] = 1;
	newCommand[1] = 0;
	dd->setCommand(newCommand);
	dd->setCommandTime(time(0));
	command[0] = 1;
	command[1] = 0;
}
