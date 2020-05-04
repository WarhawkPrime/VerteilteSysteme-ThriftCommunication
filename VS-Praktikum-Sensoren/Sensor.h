#pragma once

#include <iostream>
#include <ctime>
#include <random>
#include <chrono>
#include <thread>

#include "UDPclient.h"


class Sensor
{
public:
	Sensor();

	//Konstruktor um die jeweiligen Sensoren zu erstellen
	Sensor(double lowEnd, double highEnd, std::string type);

	//erstellt einen Zufallswert f�r die Daten
	double randomValue(double lowEnd, double highEnd);

	//berechnet die aktuelle lokale Zeit
	char* getTime();

	//f�hrt die erstellung der Daten und das senden von diesen wiederholend in einen bestimmten Zeitraum aus
	void repeater(double lowEnd, double highEnd);

	char* buildMessage();

	//========== Getter & Setter ==========
	std::string getType() const { return type;}
	void setType(std::string type) {this->type = type;}

	double getData() const { return data; }
	void setData(double data) { this->data = data; }

private:
	std::string type;	//type des jeweiligen Sensors: Temperatur, Helligkeit, Wind, Luftfeuchtigkeit, Niederschlag
	char* now;			//aktuelle Zeit und Datum
	double data;		//Der tats�chliche Wert den der Sensor zur�ck gibt, soll im Vern�nftigen Rahmen der jeweiligen Sensorart bleiben

	UDPclient udpc;		//UDP socket
};

