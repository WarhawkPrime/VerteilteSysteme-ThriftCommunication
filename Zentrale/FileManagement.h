#pragma once

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <streambuf>

class FileManagement
{
private:

	std::ofstream OutFile;
	std::ifstream InFile;
	std::vector<std::string>* filenames;
	bool f_exists(const std::string& filename);
	bool init_success;

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
	std::string readLineFromFile(const std::string filename, int line); // Returns line at the given line number, starting at beginning of file
	std::string readLineFromFile(const std::string filename, int line, bool inverted); // Overload of readLineFromFile(), allows for reverse reading from file
	std::vector<std::string> readFile(const std::string filename); // Returns entire file content as vector
	bool writeToFile(const std::string filename, const std::string data); // Writes to end of given file
};

