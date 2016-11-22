#include "stdafx.h"
#include "TurnedOn.h"

void TurnedOn::turnOff(Context * c)
{
	int zadataTemperatura = 0;
	int trenutnaTemperatura = 0;
	AnalogInput *zadTemp;
	AnalogOutput *tmpTemp;
	for (int i = 0; i < c->getCommandingEngine()->getRTU()->getAnalogInputs().size(); i++) {
		if (c->getCommandingEngine()->getRTU()->getAnalogInputs().at(i)->getName() == "ZADATA_TEMPERATURA") {
			zadataTemperatura = c->getCommandingEngine()->getRTU()->getAnalogInputs().at(i)->getRaw();
			zadTemp = c->getCommandingEngine()->getRTU()->getAnalogInputs().at(i);
			break;
		}
	}

	for (int i = 0; i < c->getCommandingEngine()->getRTU()->getAnalogOutputs().size(); i++) {
		if (c->getCommandingEngine()->getRTU()->getAnalogOutputs().at(i)->getName() == "TRENUTNA_TEMPERATURA") {
			trenutnaTemperatura = c->getCommandingEngine()->getRTU()->getAnalogOutputs().at(i)->getRaw();
			tmpTemp = c->getCommandingEngine()->getRTU()->getAnalogOutputs().at(i);
			break;
		}
	}

	c->getCommandingEngine()->getRTU()->getDigitalDevices().at(0)->setState(DigitalDevice::ON);
	c->getCommandingEngine()->getRTU()->getDigitalDevices().at(0)->setStatus(DigitalDevice::FINISHED);

	while (trenutnaTemperatura <= zadataTemperatura) {
		char request[5];
		Util::createRequest(request, nullptr, nullptr, tmpTemp, 0, -1);
		char *wholeRequest = new char[12];
		TCPDriver::getInstance().createRequest(request, wholeRequest);
		TCPDriver::getInstance().sendRequest(wholeRequest, c->getCommandingEngine()->getResponse());
		Sleep(1000);
	}
	c->setCurrent(new TurnOff());
	c->turnOff();
}
