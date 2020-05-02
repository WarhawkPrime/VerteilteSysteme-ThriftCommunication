#include "SensorManagement.h"

SensorManagement::SensorManagement()
{

}

SensorManagement::~SensorManagement()
{
	delete sensor;
	sensor = NULL;
}

void SensorManagement::createTemperatureSensor() 
{
	Sensor* s = new Sensor(0, 30, "temperatursensor");
	setSensor(s);
}

void SensorManagement::createBrightnessSensor()
{
	Sensor* s = new Sensor(50, 1200, "helligkeitssensor");
	setSensor(s);
}

void SensorManagement::createWindSensor()
{
	Sensor* s = new Sensor(0, 80, "windsensor");
	setSensor(s);
}

void SensorManagement::createHumiditySensor()
{
	Sensor* s = new Sensor(0, 100, "luftfeuchtigkeitssensor");
	setSensor(s);
}


void SensorManagement::userDialog() 
{
	int input = 1;
	std::cout << "Bitte Aktion eingeben" << std::endl;
	std::cout << "1 : Neuen Temperatur-Sensor erstellen" << std::endl;
	std::cout << "2 : Neuen Helligkeits-Sensor erstellen" << std::endl;
	std::cout << "3 : Neuen Wind-Sensor erstellen" << std::endl;
	std::cout << "4 : Neuen Luftfeuchtigkeits-Sensor erstellen" << std::endl;
	std::cout << "0 : Programm beenden" << std::endl;

	while (input = !0) {
		std::cin >> input;
		switch (input)
		{
		default: return;
			break;
		case 1:
			createTemperatureSensor(); std::cout << "erstellt"; break;
		case 2:
			createBrightnessSensor(); break;
		case 3:
			createWindSensor(); break;
		case 4:
			createHumiditySensor(); break;
		}
	}
	return;
}
