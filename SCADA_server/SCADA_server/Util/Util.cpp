#include "stdafx.h"
#include "Util.h"

/*enum status convertToStatus(int m_status) {
	switch (m_status) {
	case 0:
		return (status)DigitalDevice::FINISHED;
	case 1:
		return (status)DigitalDevice::IN_PROGRESS;
	default:
		return (status)DigitalDevice::FINISHED;
	}
}*/

RemoteTelemetryUnit *Util::parseXMLConfig()
{
	int analogInputSize = 0;
	int analogOutputSize = 0;
	int digitalDeviceInputSize = 0;
	int digitalDeviceOutputSize = 0;
	RemoteTelemetryUnit *rtu1;
	AnalogInput *ai;
	DigitalDevice *dd1;
	std::vector<AnalogInput*> analogInputs;
	std::vector<AnalogOutput*> analogOutputs;
	std::vector<DigitalDevice*> digitalDevices;

	//RTU properties
	std::string RTUname;
	std::string RTUid;
	std::string RTUindustrialProtocol;
	std::string RTUtransportProtocol;
	std::string RTUipAddress;
	int RTUport;

	//analog input properties
	std::string analogInputName;
	short analogInputAddress;
	double analogInputEGUMin;
	double analogInputEGUMax;
	short analogInputRawMin;
	short analogInputRawMax;
	short analogInputRaw;
	double analogInputValue;
	char analogInputStatus;

	//digital device properties
	std::string digitalDeviceName;
	bool readOnly;
	short inAddress1;
	short inAddress2;
	short outAddress1;
	short outAddress2;
	short inAddress[2];
	short outAddress[2];
	enum status digitalDeviceStatus;

	pugi::xml_document doc;
	if (!doc.load_file("../Util/ConfigurationXML.xml")) {
		std::cout << "Unable to load configuration file!" << std::endl;
		return NULL;
	}

	pugi::xml_node rtu = doc.child("RTU");
	RTUname = rtu.name();

	for (pugi::xml_node rtuChild = rtu.first_child(); rtuChild; rtuChild = rtuChild.next_sibling())
	{
		std::string childName = rtuChild.name();

		if (childName.compare("id") == 0) {
			RTUid = rtuChild.child_value();
			continue;
		}

		if (childName.compare("industrial_protocol") == 0) {
			RTUindustrialProtocol = rtuChild.child_value();
			continue;
		}

		if (childName.compare("transport_protocol") == 0) {
			RTUtransportProtocol = rtuChild.child_value();
			continue;
		}

		if (childName.compare("ip_address") == 0) {
			RTUipAddress = rtuChild.child_value();
			continue;
		}

		if (childName.compare("port") == 0) {
			RTUport = std::stoi(rtuChild.child_value());
			continue;
		}

		if (childName.compare("analog_input") == 0) {
			analogInputSize++;
			for (pugi::xml_node_iterator it = rtuChild.children().begin(); it != rtuChild.children().end(); ++it)
			{
				std::string inputName = it->name();

				if (inputName.compare("ai_name") == 0) {
					analogInputName = it->child_value();
					continue;
				}

				if (inputName.compare("address") == 0) {
					analogInputAddress = (short)std::stoi(it->child_value());
					continue;
				}

				if (inputName.compare("EGUMin") == 0) {
					analogInputEGUMin = std::stod(it->child_value());
					continue;
				}

				if (inputName.compare("EGUMax") == 0) {
					analogInputEGUMax = std::stod(it->child_value());
					continue;
				}

				if (inputName.compare("RawMin") == 0) {
					analogInputRawMin = (short)std::stoi(it->child_value());
					continue;
				}

				if (inputName.compare("RawMax") == 0) {
					analogInputRawMax = (short)std::stoi(it->child_value());
					continue;
				}

				if (inputName.compare("Value") == 0) {
					analogInputRaw = (short)std::stoi(it->child_value());
					continue;
				}

				if (inputName.compare("Raw") == 0) {
					analogInputValue = std::stod(it->child_value());
					continue;
				}

				if (inputName.compare("ai_Status") == 0) {
					analogInputStatus = *it->child_value();
					//continue;
				}

				ai = new AnalogInput(analogInputName, analogInputAddress, analogInputEGUMin, analogInputEGUMax, analogInputRawMin, analogInputRawMax, analogInputRaw, analogInputValue, analogInputStatus);
				analogInputs.push_back(ai);
				continue;
			}
		}

		if (childName.compare("digital_device") == 0) {
			digitalDeviceInputSize++;
			for (pugi::xml_node_iterator it = rtuChild.children().begin(); it != rtuChild.children().end(); ++it)
			{
				std::string inputName = it->name();

				if (inputName.compare("dd_name") == 0) {
					digitalDeviceName = it->child_value();
					continue;
				}

				if (inputName.compare("read_only") == 0) {
					readOnly = (bool)it->child_value();
					continue;
				}

				if (inputName.compare("in_address1") == 0) {
					inAddress1 = (short)std::stoi(it->child_value());
					inAddress[0] = inAddress1;
					continue;
				}

				if (inputName.compare("in_address2") == 0) {
					inAddress2 = (short)std::stoi(it->child_value());
					inAddress[1] = inAddress2;
					continue;
				}

				if (inputName.compare("out_address1") == 0) {
					outAddress1 = (short)std::stoi(it->child_value());
					outAddress[0] = outAddress1;
					continue;
				}

				if (inputName.compare("out_address2") == 0) {
					outAddress2 = (short)std::stoi(it->child_value());
					outAddress[1] = outAddress2;
					continue;
				}

				if (inputName.compare("dd_status") == 0) {
					//digitalDeviceStatus = convertToStatus(std::stoi(it->child_value()));
				}

				dd1 = new DigitalDevice(digitalDeviceName, readOnly, inAddress, outAddress);
				//dd1->setStatus(digitalDeviceStatus);
				digitalDevices.push_back(dd1);
				continue;
			}
		}
		if (childName.compare("analog_output") == 0) {
			analogOutputSize++;
			continue;
		}
	}

	return rtu1 = new RemoteTelemetryUnit(RTUname, RTUindustrialProtocol, RTUtransportProtocol, RTUipAddress, RTUport, analogInputSize, analogOutputSize, digitalDeviceInputSize, digitalDeviceOutputSize, analogInputs, analogOutputs, digitalDevices);
}

int Util::getSharedMesageSize(Buffer *sharedBuffer)
{
	return *(int*)sharedBuffer->getData();
}

int Util::getSharedResponseSize(Buffer *sharedBuffer)
{
	return (*(int*)(sharedBuffer->getData() + 4));
}


