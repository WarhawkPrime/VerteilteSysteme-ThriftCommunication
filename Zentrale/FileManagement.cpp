#include "FileManagement.h"

FileManagement::FileManagement() {

	this->init_success = true;
	this->filenames = new std::vector<std::string>();
	this->filenames->push_back("tempSensorData.txt");
	this->filenames->push_back("hmdtySensorData.txt");
	this->filenames->push_back("luxSensorData");
	this->filenames->push_back("airspdSensorData.txt");
	this->filenames->push_back("allSensorData.txt");



	//Check files and create if necessary
	for (int i = 0; i < filenames->size(); i++)
	{
		if (!f_exists(filenames->at(i))) {

			std::fstream file;
			file.open(filenames->at(i));
			if (!file.rdstate()) {
				std::cout << "Failed to open file. Error state: " << file.rdstate() << std::endl;
				filenames->erase(filenames->begin() + i);
				//this->init_success = false;
				return;
			}
		}
	}
}

FileManagement::~FileManagement() {


}

bool FileManagement::f_exists(const std::string& filename) {

	std::ifstream ifile(filename.c_str());
	return (bool)ifile;
}

std::string FileManagement::readLineFromFile(const std::string filename, int line) {

	return readLineFromFile(filename, line, false);
}


std::string FileManagement::readLineFromFile(const std::string filename, int line, bool inverted) {

	std::string lineString;
	std::vector<std::string> lines;
	int lineCount = 0;
	InFile.open(filename, std::ios::app);

	if (InFile.is_open()) {

		while (std::getline(InFile, lineString)) {

			lines.push_back(lineString);
		}

		InFile.close();
		lineCount = (lines.size() - 1);

		line < 0 ? line = 0 : (line > lineCount ? line = lineCount : line = line);
			
		if (inverted) {
			return lines.at((lineCount - line));
		}
		else {
			return lines.at(line);
		}
	}

}


std::vector<std::string> FileManagement::readFile(const std::string filename) {

	std::string lineString;
	std::vector<std::string> lines;

	InFile.open(filename, std::ios::app);

	if (InFile.is_open()) {

		while (std::getline(InFile, lineString)) {

			lines.push_back(lineString);
		}
		InFile.close();
		return lines;
	}
	else {
		std::cout << "Couldn't open " << filename << "!" << std::endl;
	}
}

int FileManagement::getNextLineNumber(const std::string filename) {

	InFile.open(filename);
	long lineId = 0;
	long tmp = 0;
	std::string lineString;

	if (InFile.is_open()) {

		while (std::getline(InFile, lineString, '\n')) {

			std::stringstream ss(lineString);
			std::string s;
			int counter = 0;

			while (std::getline(ss, s, ';')) {
				if (counter == 0) {
					std::istringstream(s) >> tmp;
					if (tmp >= lineId) {
						lineId = tmp;
					}
					break;
				}
				counter++;
			}
		}

		lineId++;
		return lineId;
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