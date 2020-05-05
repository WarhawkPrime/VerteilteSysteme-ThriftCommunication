#include "SensorManagement.h"

SensorManagement::SensorManagement()
{

}

SensorManagement::~SensorManagement()
{
	delete sensor;
	sensor = NULL;
}

void SensorManagement::create_temperatureSensor(int mod) 
{
	Sensor* s = new Sensor(0, 30, "temperatursensor", mod);
	set_sensor(s);
}

void SensorManagement::create_brightnessSensor(int mod)
{
	Sensor* s = new Sensor(50, 1200, "helligkeitssensor", mod);
	set_sensor(s);
}

void SensorManagement::create_windSensor(int mod)
{
	Sensor* s = new Sensor(0, 80, "windsensor", mod);
	set_sensor(s);
}

void SensorManagement::create_humiditySensor(int mod)
{
	Sensor* s = new Sensor(0, 100, "luftfeuchtigkeitssensor", mod);
	set_sensor(s);
}


void SensorManagement::user_dialog() 
{
	int input_1;
	std::cout << "Modus auswählen: Manuell oder Automatik:" << std::endl;
	std::cout << "1 : Manuell" << std::endl;
	std::cout << "2 : Automatik" << std::endl;
	std::cin >> input_1;
	switch (input_1)
	{
	default: return;
		break;
	case 1:
		std::cout << "1 : Manuell" << std::endl;
		modus = 1; break;
	case 2:
		std::cout << "1 : Automatik" << std::endl;
		modus = 2; break;
	}


	int input_2 = 0;
	std::cout << "Bitte Aktion eingeben" << std::endl;
	std::cout << "1 : Neuen Temperatur-Sensor erstellen" << std::endl;
	std::cout << "2 : Neuen Helligkeits-Sensor erstellen" << std::endl;
	std::cout << "3 : Neuen Wind-Sensor erstellen" << std::endl;
	std::cout << "4 : Neuen Luftfeuchtigkeits-Sensor erstellen" << std::endl;
	std::cout << "0 : Programm beenden" << std::endl;

	std::cin >> input_2;
	switch (input_2)
	{
	default: return;
		break;
	case 1:
		std::cout << "Temperatursensor erstellt"; 
		create_temperatureSensor(modus); break;
	case 2:
		std::cout << "Helligkeitssensor erstellt"; 
		create_brightnessSensor(modus); break;
	case 3:
		std::cout << "Windgeschwindigkeitssensor erstellt"; 
		create_windSensor(modus); break;
	case 4:
		std::cout << "Luftfeuchtigkeitssensor erstellt"; 
		create_humiditySensor(modus); break;
	}
	return;
}
