#include "stdafx.h"
#include "TurnedOff.h"

void TurnedOff::turnOn(Context * c)
{
	int spoljasnjaTemp = 0;
	int unutrasnjaTemp = 0;
	int zadataTemp = 0;
	int trenutnaTemp = 0;
	AnalogInput *spoljTemp, *unutTemp, *zadTemp;
	AnalogOutput *tmpTemp;
	for (int i = 0; i < c->getCommandingEngine()->getRTU()->getAnalogInputs().size(); i++) {
		if (c->getCommandingEngine()->getRTU()->getAnalogInputs().at(i)->getName() == "SPOLJASNJA_TEMPERATURA") {
			spoljasnjaTemp = c->getCommandingEngine()->getRTU()->getAnalogInputs().at(i)->getRaw();
			spoljTemp = c->getCommandingEngine()->getRTU()->getAnalogInputs().at(i);
			break;
		}
	}

	for (int i = 0; i < c->getCommandingEngine()->getRTU()->getAnalogInputs().size(); i++) {
		if (c->getCommandingEngine()->getRTU()->getAnalogInputs().at(i)->getName() == "UNUTRASNJA_TEMPERATURA") {
			unutrasnjaTemp = c->getCommandingEngine()->getRTU()->getAnalogInputs().at(i)->getRaw();
			unutTemp = c->getCommandingEngine()->getRTU()->getAnalogInputs().at(i);
			break;
		}
	}

	for (int i = 0; i < c->getCommandingEngine()->getRTU()->getAnalogInputs().size(); i++) {
		if (c->getCommandingEngine()->getRTU()->getAnalogInputs().at(i)->getName() == "ZADATA_TEMPERATURA") {
			zadataTemp = c->getCommandingEngine()->getRTU()->getAnalogInputs().at(i)->getRaw();
			zadTemp = c->getCommandingEngine()->getRTU()->getAnalogInputs().at(i);
			break;
		}
	}

	for (int i = 0; i < c->getCommandingEngine()->getRTU()->getAnalogOutputs().size(); i++) {
		if (c->getCommandingEngine()->getRTU()->getAnalogOutputs().at(i)->getName() == "TRENUTNA_TEMPERATURA") {
			trenutnaTemp = c->getCommandingEngine()->getRTU()->getAnalogOutputs().at(i)->getRaw();
			tmpTemp = c->getCommandingEngine()->getRTU()->getAnalogOutputs().at(i);
			break;
		}
	}

	c->getCommandingEngine()->getRTU()->getDigitalDevices().at(0)->setState(DigitalDevice::OFF);
	c->getCommandingEngine()->getRTU()->getDigitalDevices().at(0)->setStatus(DigitalDevice::FINISHED);

	while (trenutnaTemp >= 0.7*zadataTemp) {
		char request[5];
		Util::createRequest(request, nullptr, nullptr, tmpTemp, 0, -1);
		char *wholeRequest = new char[12];
		TCPDriver::getInstance().createRequest(request, wholeRequest);
		TCPDriver::getInstance().sendRequest(wholeRequest, c->getCommandingEngine()->getResponse());
		Sleep(1000);
	}
	c->setCurrent(new TurnOn());
	c->turnOn();
}
