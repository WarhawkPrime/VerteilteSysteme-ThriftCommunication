#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>


class TelemetryData {

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
	

	TelemetryData();
	~TelemetryData();
	
};
