#include "Sensor_Management.h"

void Sensor_Management::set_Sensor_ID(std::string id) {
	sensor->setID(id);
}


int Sensor_Management::firstTest()
{
	int a = 1;
	int b = 1;
	return a + b;
}

Sensor_Management::Sensor_Management()
{

}

Sensor_Management::~Sensor_Management()
{
	sensor = NULL;
}

void Sensor_Management::create_temperatureSensor(int mod, std::string id)
{
	Sensor* s = new Sensor(0, 30, "temperatursensor", mod);
	s->setID(id);
	set_sensor(s);
}

void Sensor_Management::create_brightnessSensor(int mod, std::string id)
{
	Sensor* s = new Sensor(50, 1200, "helligkeitssensor", mod);
	s->setID(id);
	set_sensor(s);
}

void Sensor_Management::create_windSensor(int mod, std::string id)
{
	Sensor* s = new Sensor(0, 80, "windsensor", mod);
	s->setID(id);
	set_sensor(s);
}

void Sensor_Management::create_humiditySensor(int mod, std::string id)
{
	Sensor* s = new Sensor(0, 100, "luftfeuchtigkeitssensor", mod);
	s->setID(id);
	set_sensor(s);
}


void Sensor_Management::user_dialog(std::string id)
{
	std::cout << "test1" << std::endl;
	std::cout << id << std::endl;


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
		create_temperatureSensor(modus, id);
		break;
	case 2:
		std::cout << "Helligkeitssensor erstellt";
		create_brightnessSensor(modus, id);
		break;
	case 3:
		std::cout << "Windgeschwindigkeitssensor erstellt";
		create_windSensor(modus, id);
		break;
	case 4:
		std::cout << "Luftfeuchtigkeitssensor erstellt";
		create_humiditySensor(modus, id);
		break;
	case 0:
		break;
	}
	return;
}





