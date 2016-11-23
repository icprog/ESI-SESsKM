#include "stdafx.h"
#include "CommandingEngine.h"

void CommandingEngine::popFromBuffer(CommandingEngine * that)
{

	while (that->getCommandingBuffer()->size() > 0) {

		// skini komandu sa bafera

		// format komande:
		//				 4 byte duzina + 5 byte drugi deo requesta
		char *command = new char[9];
		command = that->getCommandingBuffer()->pop();
		char *req = new char[9];
		int size = *((int *)command);
		if (size == 9) {  // u pitanju je prava komanda
			TCPDriver::getInstance().createRequest(command + 4, req);
			TCPDriver::getInstance().sendRequest(req);
		}
		else if(size == 6) { // u pitanjue je rad sa alarmom
			for (int i = 0; i < that->getRtu()->getAlarms()->size(); i++) {
				if (that->getRtu()->getAlarms()->at(i).getAddress() == ntohs(*((short *)(command + 4)))) {
					that->getRtu()->getAlarms()->at(i).setConfirmed(true);
					break;
				}
			}
		}
		else if (size == 8) { // u pitanjue je integrity update
			// prodji kroz ceo model i napuni stream buffer
		}
		delete req, req = 0;
		delete command, command = 0;
	}
}

void CommandingEngine::turnOnHeater(CommandingEngine * that)
{
	while (!that->getHeaterOn()) {
		char *command = new char[9];
		*((int *)command) = 9;
		command[4] = 0x06;

	}

}
