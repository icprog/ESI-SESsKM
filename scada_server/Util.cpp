#include "stdafx.h"
#pragma pack(1)
#include <fstream>
#include <string>
#include<iostream>
#include "Util.h"
#include "AnalogInput.h"
#include "RTU.h"
#include "Buffer.h"
#include "DataProcessingEngine.h"
using namespace std;

void Util::initialize(char *arr1, char *arr2, int startIdx, int endIdx, int j)
{
	for (int i = startIdx, k = j; i < endIdx; i++, k++) {
		arr1[k] = arr2[i];
	}
}

void Util::readFromFile(RTU *rt1)
{
	std::vector<AnalogInput> analogInputs;
	std::vector<AnalogOutput> analogOutputs;
	std::vector<DigitalDevice> digitalDevices;

	//vrednosti koje popunjavam za rtu
	string RTUName;
	string RTUIpAdress;
	int RTUport;
	//
	//vrednosti za zadatu temperaturu ANALOG INPUT 1
	string ZadataTempName;
	int ZadataTempAdress;
	int ZadataTempEGUMin;
	int ZadataTempEGUMax;
	int ZadataTempEGU;
	int ZadataTempRawMin;
	int ZadataTempRawMax;
	int ZadataTempRaw;
	int ZadataTempValue;
	//
	//vrednosti za spoljasnju temperaturu ANALOG INPUT 2
	string SpTempName;
	int SpTempAdress;
	int SpTempEGUMin;
	int SpTempEGUMax;
	int SpTempEGU;
	int SpTempRawMin;
	int SpTempRawMax;
	int SpTempRaw;
	int SpTempValue;
	//
	//vrednosti za unutrasnju temperaturu ANALOG INPUT 3
	string UnTempName;
	int UnTempAdress;
	int UnTempEGUMin;
	int UnTempEGUMax;
	int UnTempEGU;
	int UnTempRawMin;
	int UnTempRawMax;
	int UnTempRaw;
	int UnTempValue;
	//
	//vrednosti za stanje grejaca DIGITAL INPUT 1
	string StGrejacaName;
	int StGrejacReadOnly;
	int StGrejacInAdress1;
	int StGrejacInAdress2;
	int StGrejacOutAdress1;
	int StGrejacOutAdress2;
	int StGrejacStatus;
	//char StGrejacState;
	//

	ifstream inFile;
	inFile.open("Configuration.txt");
	string str;
	string delimiter = ";";
	string fileContent;
	string token;
	while (getline(inFile, str)) {
		//cout << str <<endl;
		fileContent += str;
		fileContent.push_back('\n');
	}

	size_t pos = 0;
	int i = 0;
	while ((pos = fileContent.find(delimiter)) != std::string::npos) {

		token = fileContent.substr(0, pos);

		if (i == 0)
			RTUName = token;

		if (i == 1)
			RTUIpAdress = token;

		if (i == 2)
			RTUport = stoi(token);

		if (i == 3)
			ZadataTempName = token;

		if (i == 4)
			ZadataTempAdress = stoi(token);

		if (i == 5)
			ZadataTempEGUMin = stoi(token);

		if (i == 6)
			ZadataTempEGUMax = stoi(token);

		if (i == 7)
			ZadataTempEGU = stoi(token);

		if (i == 8)
			ZadataTempRawMin = stoi(token);

		if (i == 9)
			ZadataTempRawMax = stoi(token);

		if (i == 10)
			ZadataTempRaw = stoi(token);

		if (i == 11)
			ZadataTempValue = stoi(token);

		if (i == 12)
			SpTempName = token;

		if (i == 13)
			SpTempAdress = stoi(token);

		if (i == 14)
			SpTempEGUMin = stoi(token);

		if (i == 15)
			SpTempEGUMax = stoi(token);

		if (i == 16)
			SpTempEGU = stoi(token);

		if (i == 17)
			SpTempRawMin = stoi(token);

		if (i == 18)
			SpTempRawMax = stoi(token);

		if (i == 19)
			SpTempRaw = stoi(token);

		if (i == 20)
			SpTempValue = stoi(token);

		if (i == 21)
			UnTempName = token;

		if (i == 22)
			UnTempAdress = stoi(token);

		if (i == 23)
			UnTempEGUMin = stoi(token);

		if (i == 24)
			UnTempEGUMax = stoi(token);

		if (i == 25)
			UnTempEGU = stoi(token);

		if (i == 26)
			UnTempRawMin = stoi(token);

		if (i == 27)
			UnTempRawMax = stoi(token);

		if (i == 28)
			UnTempRaw = stoi(token);

		if (i == 29)
			UnTempValue = stoi(token);

		if (i == 30)
			StGrejacaName = token;

		if (i == 31)
			StGrejacReadOnly = stoi(token);

		if (i == 32)
			StGrejacInAdress1 = stoi(token);

		if (i == 33)
			StGrejacInAdress2 = stoi(token);

		if (i == 34)
			StGrejacOutAdress1 = stoi(token);

		if (i == 35)
			StGrejacOutAdress2 = stoi(token);

		if (i == 36)
			StGrejacStatus = stoi(token);

		//std::cout << token << std::endl;
		fileContent.erase(0, pos + delimiter.length());
		i++;
	}

	
	cout << "RTU name: " << RTUName << endl;
	cout << "RTU ip adress: " << RTUIpAdress << endl;
	cout << "RTU port: " << RTUport << endl;

	cout << "Zadata temp. name: " << ZadataTempName << endl;
	cout << "Zadata temp. adress: " << ZadataTempAdress << endl;
	cout << "Zadata temp. EGU min: " << ZadataTempEGUMin << endl;
	cout << "Zadata temp. EGU max: " << ZadataTempEGUMax << endl;
	cout << "Zadata temp. EGU: " << ZadataTempEGU << endl;
	cout << "Zadata temp. Raw min: " << ZadataTempRawMin << endl;
	cout << "Zadata temp. Raw max: " << ZadataTempRawMax << endl;
	cout << "Zadata temp. Raw: " << ZadataTempRaw << endl;
	cout << "Zadata temp. value: " << ZadataTempValue << endl;
	AnalogInput *ai3 = new AnalogInput(ZadataTempName, ZadataTempAdress, ZadataTempEGUMin, ZadataTempEGUMax, ZadataTempEGU, ZadataTempRawMin, ZadataTempRawMax, ZadataTempRaw, ZadataTempValue);

	cout << "Spoljasnja temp. name: " << SpTempName << endl;
	cout << "Spoljasnja temp. ip adress: " << SpTempAdress << endl;
	cout << "Spoljasnja temp. EGU min: " << SpTempEGUMin << endl;
	cout << "Spoljasnja temp. EGU max: " << SpTempEGUMax << endl;
	cout << "Spoljasnja temp. EGU: " << SpTempEGU << endl;
	cout << "Spoljasnja temp. Raw min: " << SpTempRawMin << endl;
	cout << "Spoljasnja temp. Raw max: " << SpTempRawMax << endl;
	cout << "Spoljasnja temp. Raw: " << SpTempRaw << endl;
	cout << "Spoljasnja temp. value: " << SpTempValue << endl;
	AnalogInput *ai1 = new AnalogInput(SpTempName, SpTempAdress, SpTempEGUMin, SpTempEGUMax, SpTempEGU, SpTempRawMin, SpTempRawMax, SpTempRaw, SpTempValue);

	cout << "Unutrasnja temp. name: " << UnTempName << endl;
	cout << "Unutrasnja temp. ip adress: " << UnTempAdress << endl;
	cout << "Unutrasnja temp. EGU min: " << UnTempEGUMin << endl;
	cout << "Unutrasnja temp. EGU max: " << UnTempEGUMax << endl;
	cout << "Unutrasnja temp. EGU: " << UnTempEGU << endl;
	cout << "Unutrasnja temp. Raw min: " << UnTempRawMin << endl;
	cout << "Unutrasnja temp. Raw max: " << UnTempRawMax << endl;
	cout << "Unutrasnja temp. Raw: " << UnTempRaw << endl;
	cout << "Unutrasnja temp. Raw value: " << UnTempValue << endl;
	AnalogInput *ai2 = new AnalogInput(UnTempName, UnTempAdress, UnTempEGUMin, UnTempEGUMax, UnTempEGU, UnTempRawMin, UnTempRawMax, UnTempRaw, UnTempValue);

	cout << "Stanje grejaca name: " << StGrejacaName << endl;
	cout << "Stanje grejaca read only: " << StGrejacReadOnly << endl;
	cout << "Stanje grejaca in adress1: " << StGrejacInAdress1 << endl;
	cout << "Stanje grejaca in adress2: " << StGrejacInAdress2 << endl;
	cout << "Stanje grejaca out adress1: " << StGrejacOutAdress1 << endl;
	cout << "Stanje grejaca out adress2: " << StGrejacOutAdress2 << endl;
	cout << "Stanje grejaca status: " << StGrejacStatus << endl;

	char state = 0;
	//char command[2];
	//command[0] = 0;
	//command[1] = 0;
	DigitalDevice *dd1 = new DigitalDevice(StGrejacaName, StGrejacReadOnly, StGrejacInAdress1, StGrejacInAdress2, StGrejacOutAdress1, StGrejacOutAdress2, StGrejacStatus);
	//dd1->setState(state);
	//dd1->setCommand(command);
	analogInputs.push_back(*ai1);
	analogInputs.push_back(*ai2);
	digitalDevices.push_back(*dd1);
	int analogInputNum = analogInputs.size();
	int analogOutputNum = analogOutputs.size();
	int digInputNum = digitalDevices.size();
	
	//int digOutputNum


	rt1 = new RTU(RTUName, "Modbus", "TCP/IP", RTUIpAdress, RTUport, analogInputNum, analogOutputNum, digInputNum, digInputNum, &analogInputs, &analogOutputs, &digitalDevices);

	CRITICAL_SECTION cs;
	InitializeCriticalSection(&cs);

	Buffer *b1 = new Buffer("buf11", 512, &cs);
	char data[11];
	//response u bafer
	data[0]= 0x00; //tcp header
	data[1] = 0x01;
	data[2] = 0x00;
	data[3] = 0x00;
	data[4] = 0x00; 
	data[5] = 0x05;
	data[6] = 0x01;

	data[7] = 0x04; //fun. code
	data[8] = 0x01;
	data[9] = 0x00;
	data[10] = 0x01;

	b1->push(data);
	char sa[2];
	/* 4001 FA1
	sa[0] = 0x0F;
	sa[1] = 0xA1;
	*/
	/* 1
	sa[0] = 0x00;
	sa[1] = 0x01;
	*/
	DataProcessing *dp = new DataProcessing();
	dp->dataProcessingEngine(b1, sa, rt1);
	
	inFile.close();
}


