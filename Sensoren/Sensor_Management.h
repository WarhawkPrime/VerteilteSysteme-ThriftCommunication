#pragma once

#include <iostream>

#include "Sensor.h"
#include "MQTT_Sensor.h"

#include <memory>
#include <utility>

#include <chrono>


class Sensor_Management
{
public:
	Sensor_Management();
	~Sensor_Management();

	void user_dialog(std::string id);
	
	//udp sensor
	//void create_temperatureSensor(int mod, std::string id);
	//void create_brightnessSensor(int mod, std::string id);
	//void create_windSensor(int mod, std::string id);
	//void create_humiditySensor(int mod, std::string id);

	//mqtt
	void create_temperatureMQTTSensor(int mod, std::string id);
	void create_brightnessMQTTSensor(int mod, std::string id);
	void create_windMQTTSensor(int mod, std::string id);
	void create_humidityMQTTSensor(int mod, std::string id);
	
	//udp sensor
	//void set_sensor(Sensor* newSensor) { this->sensor = newSensor; }
	//Sensor* get_sensor() { return sensor; }
	
	//mqtt
	void set_mqtt_sensor(MQTT_Sensor* newMQTTSensor) { this->mqttSensor = newMQTTSensor; }
	const MQTT_Sensor* get_mqttSensor() { return mqttSensor; }

	int firstTest();

	void set_Sensor_ID(std::string id);

private:
	//Sensor* sensor;
	MQTT_Sensor* mqttSensor;
	int modus;
};
