#include "stdafx.h"
#include "DataProcessingEngine.h"

#define BUFFER_SIZE 512

void DataProcessingEngine::process(DataProcessingEngine *that)
{
	std::cout << "Obradjuju se podaci!!!" << std::endl;
	Buffer *sharedBuffer = that->getSharedBuffer();
	RemoteTelemetryUnit *rtu = that->getRTU();
	while (1) {
		while (sharedBuffer->getPopIdx() != sharedBuffer->getPushIdx()) {
			//dobijemo velicinu poruke i responsa iz shared buffera
			int messageLength = Util::getSharedMesageSize(sharedBuffer);
			int responseLength = Util::getSharedResponseSize(sharedBuffer);

			//niz u koji smestam poruku koju skinem sa shared buffera
			char dataBuf[BUFFER_SIZE];
			memset(dataBuf, 0, BUFFER_SIZE);
			sharedBuffer->pop(dataBuf, messageLength);

			//uzimamo adresu i function code iz poruke
			short address = ntohs(*((short*)(dataBuf + 8 + responseLength + 8))); //8 bajta duzine,  response size ,i onda jos 8 bajta u req    27
			char fCode = *((char*)(dataBuf + 8 + 7)); //dataBuf +4(za duzinu cele poruke) +4(duzina responsa) +7(response header)

			if (fCode == 1) {  //citanje digitalnih izlaza
				char outputValue = *((char*)(dataBuf + 17)); //status dig.izlaza
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
				}
			}
			else if (fCode == 2) { //citanje digitalnih ulaza
				char outputValue = *((char*)(dataBuf + 17)); //status dig.izlaza
				//upisi u digitalni ulaz
				std::vector<DigitalDevice*> digitalDevices = rtu->getDigitalDevices();

				for (int i = 0; i < digitalDevices.size(); i++) {
					DigitalDevice *it = digitalDevices.at(i);
					short *inAddresses = it->getInAddresses();
					if (inAddresses[0] == address || inAddresses[1] == address) {
						if (outputValue == 0) {
							it->setState(DigitalDevice::ON);
						}
						if (outputValue == 1) {
							it->setState(DigitalDevice::OFF);
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
		*((int *)(stream + 10)) = dd->getState();
		*((int *)(stream + 14)) = 0;
	}
	streamBuffer->push(stream, 18);
	delete stream;
}
