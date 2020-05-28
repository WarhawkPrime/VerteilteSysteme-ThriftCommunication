#pragma once

#include <iostream>

#include "Sensor.h"
#include <memory>
#include <utility>

#include <chrono>


class Sensor_Management
{
public:
	Sensor_Management();
	~Sensor_Management();

	void user_dialog(std::string id);
	void create_temperatureSensor(int mod, std::string id);
	void create_brightnessSensor(int mod, std::string id);
	void create_windSensor(int mod, std::string id);
	void create_humiditySensor(int mod, std::string id);

	void set_sensor(Sensor* newSensor) { this->sensor = newSensor; }
	Sensor* get_sensor() { return sensor; }

	int firstTest();

	void set_Sensor_ID(std::string id);

private:
	Sensor* sensor;
	int modus;
};