#pragma once

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <streambuf>
#include <sstream>
#include <netdb.h>

#define MAX_BUFFER 1024

class FileManagement
{
private:

	std::ofstream OutFile;
	std::ifstream InFile;
	std::vector<std::string>* filenames;
	bool f_exists(const std::string& filename);
	bool f_is_empty(std::ifstream& inFile);
	bool writeToFile(const std::string filename, const std::string data); // Writes to end of given file
	bool getNextLineNumber(const std::string filename, long& lineId);
	bool init_success;
	std::string airSpdFileName;
	std::string tempFileName;
	std::string allDataFileName;
	std::string hmdtyDataFileName;
	std::string lxDataFileName;

public:

	std::vector<std::string>* currentSensorInfo;

	FileManagement();
	~FileManagement();
	std::string readLineFromFile(const std::string filename, int line); // Returns line at the given line number, starting at beginning of file
	std::string readLineFromFile(const std::string filename, int line, bool inverted); // Overload of readLineFromFile(), allows for reverse reading from file
	std::vector<std::string> readFile(const std::string filename); // Returns entire file content as vector	
	std::string* writeBufferToFile(char dataBuffer[NI_MAXHOST], char hostBuffer[MAX_BUFFER], int numBytesReceived); // Writes buffer to end of file, sets id automatically
	bool writeMQTTToFile(std::string data, const std::string filename, std::string port);
	std::string getTemp() { return this->tempFileName; };
	std::string getAirspd() { return this->airSpdFileName; };
	std::string getHumidty() { return this->hmdtyDataFileName; };
	std::string getLux() { return this->lxDataFileName; };
	std::string getAll() { return this->allDataFileName; };


};

