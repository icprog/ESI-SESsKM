#include "stdafx.h"
#include "TurnOff.h"

void TurnOff::turnedOff(Context * c)
{
	c->getCommandingEngine()->getRTU()->getDigitalDevices().at(0)->setStatus(DigitalDevice::IN_PROGRESS);
	char request[5];
	Util::createRequest(request, c->getCommandingEngine()->getRTU()->getDigitalDevices().at(0), nullptr, nullptr, 0, 0);
	char *wholeRequest = new char[12];
	TCPDriver::getInstance().createRequest(request, wholeRequest);
	TCPDriver::getInstance().sendRequest(wholeRequest, c->getCommandingEngine()->getResponse());
	c->getCommandingEngine()->getSharedBuffer()->push(c->getCommandingEngine()->getResponse(), c->getCommandingEngine()->getResponseSize());
	Stopwatch<> sw;
	while (sw.timePassed() < 15) {
		Util::createRequest(request, c->getCommandingEngine()->getRTU()->getDigitalDevices().at(0), nullptr, nullptr, 1, -1);
		wholeRequest = new char[12];
		TCPDriver::getInstance().createRequest(request, wholeRequest);
		TCPDriver::getInstance().sendRequest(wholeRequest, c->getCommandingEngine()->getResponse());
		if (!c->getCommandingEngine()->turnedOn(c->getCommandingEngine())) {
			c->setCurrent(new TurnedOff());
			c->turnedOff();
		}
		else
			Sleep(200);
	}
	sw.stop();
	c->setCurrent(new AlarmState());
	c->alarm();
}
