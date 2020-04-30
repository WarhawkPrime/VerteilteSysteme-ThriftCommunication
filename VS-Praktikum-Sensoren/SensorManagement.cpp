#include "SensorManagement.h"

SensorManagement::SensorManagement()
{

}

void SensorManagement::userDialog() 
{
	int input = 1;
	std::cout << "Bitte Aktion eingeben" << std::endl;
	std::cout << "1 : Neuen Temperatur-Sensor erstellen" << std::endl;
	std::cout << "2 : Neuen Helligkeits-Sensor erstellen" << std::endl;
	std::cout << "3 : Neuen Wind-Sensor erstellen" << std::endl;
	std::cout << "4 : Neuen Luftfeuchtigkeits-Sensor erstellen" << std::endl;
	std::cout << "5 : Neuen Niederschlags-Sensor ersellen" << std::endl;
	std::cout << "0 : Programm beenden" << std::endl;

	while (input = !0) {
		std::cin >> input;
		switch (input)
		{
		default: return;
			break;
		case 1:
			std::cout << "1"; break;
		case 2:
			std::cout << "2"; break;
		case 3:
			std::cout << "3"; break;
		case 4:
			std::cout << "4"; break;
		case 5:
			std::cout << "5"; break;
		}
	}
	return;

}
