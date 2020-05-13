#pragma once

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

class Telemetry_data
{
private:

	std::ofstream jsonFile;


public:

	struct SensorData {

		int port;
		char* ip_addr;
		double data;
		time_t dateSent;
		std::string sensorType;
	};
	std::vector<SensorData> savedData;


	Telemetry_data();
	~Telemetry_data();
};

