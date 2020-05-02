#pragma once

#include <iostream>
#include <ctime>
#include <random>

//#include "UDPclient.h"


class Sensor
{
public:
	Sensor();
	~Sensor();

	Sensor(double lowEnd, double highEnd, std::string type);

	double randomValue(double lowEnd, double highEnd);

	char* getTime();

	std::string getType() const { return type;}
	void setType(std::string type) {this->type = type;}

	double getData() const { return data; }
	void setData(double data) { this->data = data; }

private:
	std::string type;	//type des jeweiligen Sensors: Temperatur, Helligkeit, Wind, Luftfeuchtigkeit, Niederschlag
	char* now;		//aktuelle Zeit und Datum
	double data;		//Der tatsächliche Wert den der Sensor zurück gibt, soll im Vernünftigen Rahmen der jeweiligen Sensorart bleiben
};

