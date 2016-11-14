#pragma once
#ifndef  PDU_H
#define PDU_H
#pragma pack(1)
#include "Util.h"
class PDU {
private:
	char functionCode;
	char startinAddress[2];
	char quantityOfCoils[2];
	char pdu[5];
public:
	void createPDU();
	PDU(char fc, char *sa, char *qoc);
	char* getPDU();
};

#endif // ! PDU_H
