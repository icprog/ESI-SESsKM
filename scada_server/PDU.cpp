#include "stdafx.h"
#include "PDU.h"

void PDU::createPDU()
{
	char t[1];
	t[0] = functionCode;
	Util::initialize(pdu, t, 0, 1, 0);
	Util::initialize(pdu, startinAddress, 0, 2, 1);
	Util::initialize(pdu, quantityOfCoils, 0, 2, 3);
}

PDU::PDU(char fc, char * sa, char * qoc)
{
	functionCode = fc;
	Util::initialize(startinAddress, sa, 0,2,0);
	Util::initialize(quantityOfCoils, qoc, 0,2,0);
	createPDU();
}

char * PDU::getPDU()
{
	return pdu;
}
