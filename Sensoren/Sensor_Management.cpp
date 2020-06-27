#include "Sensor_Management.h"

void Sensor_Management::set_Sensor_ID(std::string id) {
	//sensor->setID(id);
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
	//sensor = NULL;
}

//udp
/*
void Sensor_Management::create_temperatureSensor(int mod, std::string sid)
{
	Sensor* s = new Sensor(0, 30, "temperatursensor", mod, sid);
	set_sensor(s);
}

void Sensor_Management::create_brightnessSensor(int mod, std::string sid)
{
	Sensor* s = new Sensor(50, 1200, "helligkeitssensor", mod, sid);
	set_sensor(s);
}

void Sensor_Management::create_windSensor(int mod, std::string sid)
{
	Sensor* s = new Sensor(0, 80, "windsensor", mod, sid);
	set_sensor(s);
	
}

void Sensor_Management::create_humiditySensor(int mod, std::string sid)
{
	Sensor* s = new Sensor(0, 100, "luftfeuchtigkeitssensor", mod, sid);
	set_sensor(s);
	
}
*/




//MQTT =======================================================================
void Sensor_Management::create_temperatureMQTTSensor(int mod, std::string sid)
{
	MQTT_Sensor* s = new MQTT_Sensor(0, 30, "temperatursensor", mod, sid);
	set_mqtt_sensor(s);
}

void Sensor_Management::create_brightnessMQTTSensor(int mod, std::string sid)
{
	MQTT_Sensor* s = new MQTT_Sensor(50, 1200, "helligkeitssensor", mod, sid);
	set_mqtt_sensor(s);
}

void Sensor_Management::create_windMQTTSensor(int mod, std::string sid)
{
	MQTT_Sensor* s = new MQTT_Sensor(0, 80, "windsensor", mod, sid);
	set_mqtt_sensor(s);
	
}

void Sensor_Management::create_humidityMQTTSensor(int mod, std::string sid)
{
	MQTT_Sensor* s = new MQTT_Sensor(0, 100, "luftfeuchtigkeitssensor", mod, sid);
	set_mqtt_sensor(s);
	
}
//=============================================================================

//udp
/*
void Sensor_Management::user_dialog(std::string sid)
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
		create_temperatureSensor(modus, sid);
		break;
	case 2:
		std::cout << "Helligkeitssensor erstellt";
		create_brightnessSensor(modus, sid);
		break;
	case 3:
		std::cout << "Windgeschwindigkeitssensor erstellt";
		create_windSensor(modus, sid);
		break;
	case 4:
		std::cout << "Luftfeuchtigkeitssensor erstellt";
		create_humiditySensor(modus, sid);
		break;
	case 0:
		break;
	}
	return;
}
*/


//MQTT ====================================================================
void Sensor_Management::user_dialog(std::string sid)
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
	std::cout << "1 : Neuen Temperatur-MQTT-Sensor erstellen" << std::endl;
	std::cout << "2 : Neuen Helligkeits-MQTT-Sensor erstellen" << std::endl;
	std::cout << "3 : Neuen Wind-MQTT-Sensor erstellen" << std::endl;
	std::cout << "4 : Neuen Luftfeuchtigkeits-MQTT-Sensor erstellen" << std::endl;
	std::cout << "0 : Programm beenden" << std::endl;

	std::cin >> input_2;
	switch (input_2)
	{
	default: return;
		break;
	case 1:
		std::cout << "Temperatursensor MQTT erstellt";
		create_temperatureMQTTSensor(modus, sid);
		break;
	case 2:
		std::cout << "Helligkeitssensor MQTT erstellt";
		create_brightnessMQTTSensor(modus, sid);
		break;
	case 3:
		std::cout << "Windgeschwindigkeitssensor MQTT erstellt";
		create_windMQTTSensor(modus, sid);
		break;
	case 4:
		std::cout << "Luftfeuchtigkeitssensor MQTT erstellt";
		create_humidityMQTTSensor(modus, sid);
		break;
	case 0:
		break;
	}
	return;
}
//======================================================================================

