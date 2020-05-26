#pragma once

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

class FileManagement
{
private:

	std::ofstream* OutFile;
	std::ifstream* InFile;


public:

	struct SensorDataEntry {

		int id;
		std::string ip_addr;
		int port;
		std::string sensorType;
		double measurement;
		time_t dateSent;
		time_t dateReceived;
		
	};

	std::vector<SensorDataEntry> savedData;
	std::vector<std::string>* currentSensorInfo;

	FileManagement();
	~FileManagement();
};

