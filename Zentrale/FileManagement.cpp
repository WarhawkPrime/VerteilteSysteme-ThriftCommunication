#include "FileManagement.h"

FileManagement::FileManagement() {

	this->init_success = true;
	this->filenames = new std::vector<std::string>();
	tempFileName = "tempSensorData.txt";
	lxDataFileName = "luxSensorData.txt";
	allDataFileName = "allSensorData.txt";
	hmdtyDataFileName = "hmdtySensorData.txt";
	airSpdFileName = "airspdSensorData.txt";
	this->filenames->push_back(tempFileName);
	this->filenames->push_back(lxDataFileName);
	this->filenames->push_back(airSpdFileName);
	this->filenames->push_back(hmdtyDataFileName);
	this->filenames->push_back(allDataFileName);

	//Check files and create if necessary
	for (int i = 0; i < filenames->size(); i++)
	{
		if (!f_exists(filenames->at(i))) {


			OutFile.open(filenames->at(i), std::ios::out | std::ios::app);
			if (!OutFile.is_open()) {
				std::cout << "Failed to open file. Error state: " << OutFile.rdstate() << std::endl;
				return;
			}
			OutFile.close();
		}
	}

}

FileManagement::~FileManagement() {


}

bool FileManagement::f_exists(const std::string& filename) {

	std::ifstream ifile(filename.c_str());
	return (bool)ifile;
}

bool FileManagement::f_is_empty(std::ifstream& inFile) {

	return (inFile.peek() == std::ifstream::traits_type::eof());
}

std::string FileManagement::readLineFromFile(const std::string filename, int line) {

	return readLineFromFile(filename, line, false);
}


std::string FileManagement::readLineFromFile(const std::string filename, int line, bool inverted) {

	std::string lineString;
	std::vector<std::string> lines;
	int lineCount = 0;
	if (!f_exists(filename)) {

		OutFile.open(filename, std::ios::app);
		if (!OutFile.is_open()) {

			std::cout << "File couldn't be opened!" << std::endl;
			return "File couldn't be opened!";
		}
		OutFile.close();
	}

	InFile.open(filename, std::ios::in);

	if (InFile.is_open()) {


		while (std::getline(InFile, lineString)) {

			lines.push_back(lineString);
		}

		InFile.close();

		lineCount = (lines.size() - 1);
		if (lineCount < 0) {
			lineCount = 0;
		}
		if (line >= lines.size()) {
			line = (lines.size() - 1);
			if (line < 0) {
				line = 0;
			}
		}


		if (lines.empty()) {

			return "No data yet!";
		}
		else {

			if (inverted) {

				return lines.at((lineCount - line));
			}
			else {

				return lines.at(line);
			}
		}
	}
	else {

		std::cout << "Couldn't open file in readLineFromFile" << std::endl;
	}
	return "Bad Request";
}


std::vector<std::string> FileManagement::readFile(const std::string filename) {

	std::string lineString;
	std::vector<std::string> lines;

	if (!f_exists(filename)) {

		std::cout << "File doesn't exist." << std::endl;
	}
	else {

		InFile.open(filename);

		if (InFile.is_open()) {

			while (std::getline(InFile, lineString)) {

				lineString += "\n";
				lines.push_back(lineString);
			}
			InFile.close();
			return lines;
		}
		else {

			std::cout << "Couldn't open " << filename << "!" << std::endl;
		}
	}
}

bool FileManagement::getNextLineNumber(const std::string filename, long& lineId) {

	if (!f_exists(filename)) {

		std::cout << "File doesn't exist." << std::endl;
		return false;
	}

	InFile.open(filename);
	long tmp = 0;
	std::string lineString;

	if (InFile.is_open()) {

		while (std::getline(InFile, lineString, '\n')) {

			std::stringstream ss(lineString);
			std::string s;
			int counter = 0;

			if (lineString.empty()) {

				lineId = 0;
				break;
			}
			else {

				while (std::getline(ss, s, ';')) {

					if (counter == 0) {

						tmp = 0;
						std::istringstream(s) >> tmp;

						if (tmp >= lineId) {
							lineId = tmp;
						}
						break;
					}
					counter++;
				}
			}
		}

		lineId++;
		InFile.close();
		return true;
	}
}

std::string* FileManagement::writeBufferToFile(char dataBuffer[NI_MAXHOST], char hostBuffer[MAX_BUFFER], int numBytesReceived) {

	// Construct string of data to write
	std::string filename, token, sensorType, data(dataBuffer, numBytesReceived);
	std::string* ret = &data;
	long nextId = 0, nextIdAll = 0;
	int counter = 0, sensorId;
	std::stringstream ss(data);
	//search string for whitelist
	char delim = ';';

	// Get sensor type and ID
	while (std::getline(ss, token, delim)) {

		if (counter == 0) {

			// Set sensor ID
			sensorId = std::atoi(token.c_str());
		}
		else if (counter == 2) {

			// Type of sensor found, save it
			sensorType = token;
			break;
		}

		counter++;
	}

	data.insert(0, ";");
	data.insert(0, hostBuffer);
	data.insert(0, ";");

	std::cout << "SensorType: " << sensorType << " ID: " << sensorId << std::endl;

	if (sensorType.find("temp") != std::string::npos) {

		filename = tempFileName;
	}
	else if (sensorType.find("luft") != std::string::npos) {

		filename = hmdtyDataFileName;
	}
	else if (sensorType.find("hell") != std::string::npos) {

		filename = lxDataFileName;
	}
	else if (sensorType.find("wind") != std::string::npos) {

		filename = airSpdFileName;
	}
	else {
		// Error
		std::cout << " Couldn't find sensor type!" << std::endl;
		return NULL;
	}

	// Set line number
	std::string allData = data;
	if (getNextLineNumber(filename, nextId)) {

		data.insert(0, std::to_string(nextId));
	}
	else {
		return NULL;
	}
	if (getNextLineNumber(allDataFileName, nextIdAll)) {

		allData.insert(0, std::to_string(nextIdAll));
	}
	else {
		return NULL;
	}

	if (writeToFile(filename, data)) {

		std::cout << "Written following data to " << filename << ": " << std::endl << data << std::endl;

		if (!writeToFile(allDataFileName, allData)) {

			std::cout << "Failed to write to AllSensorData.txt" << std::endl;
			return NULL;
		}
		else {
			std::cout << "Written following data to " << allDataFileName << ": " << std::endl << allData << std::endl;
			return ret;
		}
	}
	else {

		std::cout << "Failed to write to " << filename << std::endl;
		return NULL;
	}
}

bool FileManagement::writeToFile(const std::string filename, const std::string data) {

	OutFile.open(filename, std::ios::app);

	if (OutFile.is_open()) {

		OutFile << data;
		OutFile.close();
		return true;
	}
	else {

		return false;
	}
}
