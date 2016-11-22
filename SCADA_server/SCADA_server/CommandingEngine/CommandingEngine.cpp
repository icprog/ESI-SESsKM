#include "stdafx.h"
#include "CommandingEngine.h"

void CommandingEngine::popCommand(CommandingEngine * that)
{
	// client confirms alarm inputing something on console, and client programs
	// sends to scada address of confirmed alarm( only 2 bytes)
	while (1) {
		while (that->getCommandingBuffer()->getCount() > 0) {
			char response[2];
			that->getCommandingBuffer()->pop(response, 2);
			int alarmAddress = *(short *)response;

			for (int i = 0; i < that->getRTU()->getAlarms()->size(); i++) {
				if (that->getRTU()->getAlarms()->at(i).getAddress() == alarmAddress) {
					that->getRTU()->getAlarms()->at(i).setConfirmed(true);
					break;
				}
			}
		}
	}
}

void CommandingEngine::closedLoop(CommandingEngine * that)
{
	while (1) {
		


	}
}

int CommandingEngine::turnHeaterOn(CommandingEngine * that)
{
	while (that->getRTU()->getDigitalDevices().at(0)->getStatus() == DigitalDevice::IN_PROGRESS) {
		// WAIT for status to be changed
	}
	char request[5];
	Util::createRequest(request, that->getRTU()->getDigitalDevices().at(0), nullptr, nullptr, 0);
	char *wholeRequest = new char[12];
	TCPDriver::getInstance().createRequest(request, wholeRequest);
	TCPDriver::getInstance().sendRequest(wholeRequest, response);
	sharedBuffer->push(response, getResponseSize());

}

int CommandingEngine::turnHeaterOff()
{
	return 0;
}

void CommandingEngine::sendRequest()
{
}

void CommandingEngine::receiveResponse()
{
}

bool CommandingEngine::turnedOn(CommandingEngine * that)
{
	char outputValue = *((char*)(response + 17)); //status dig.izlaza
	if (outputValue == 0x01) {
		return true;
	}else
		return false;
}
void CommandingEngine::makeAlarm(CommandingEngine *that) {

}