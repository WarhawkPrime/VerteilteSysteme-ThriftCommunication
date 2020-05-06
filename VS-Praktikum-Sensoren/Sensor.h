#pragma once

#include <iostream>
#include <ctime>
#include <random>
#include <chrono>
#include <thread>
#include <pthread.h>
#include <string>

#include "UDPclient.h"

class Sensor
{
public:
	Sensor();

	//Konstruktor um die jeweiligen Sensoren zu erstellen
	Sensor(double lowEnd, double highEnd, std::string type, int modus);

	//erstellt einen Zufallswert für die Daten
	double random_value(double lowEnd, double highEnd);

	//berechnet die aktuelle lokale Zeit
	char* getTime();

	//führt die erstellung der Daten und das senden von diesen wiederholend in einen bestimmten Zeitraum aus
	void repeater(double lowEnd, double highEnd, int modus);

	char* build_message();

	void sleep_delay();

	//========== Getter & Setter ==========
	std::string get_type() {return type;}
	void set_type(std::string type) {this->type = type;}

	double get_data()  {return data; }
	void set_data(double data) {this->data = data; }

	char* get_date() { return now; }

private:
	std::string type;	//type des jeweiligen Sensors: Temperatur, Helligkeit, Wind, Luftfeuchtigkeit, Niederschlag
	char* now;			//aktuelle Zeit und Datum
	double data;		//Der tatsächliche Wert den der Sensor zurück gibt, soll im Vernünftigen Rahmen der jeweiligen Sensorart bleiben

	UDPclient udpc;		//UDP socket
};

