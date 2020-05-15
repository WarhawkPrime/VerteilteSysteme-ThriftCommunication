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

	void user_dialog();
	void create_temperatureSensor(int mod);
	void create_brightnessSensor(int mod);
	void create_windSensor(int mod);
	void create_humiditySensor(int mod);

	void set_sensor(Sensor* newSensor) { this->sensor = newSensor; }
	Sensor* get_sensor() { return sensor; }

	int firstTest();

private:
	Sensor* sensor;
	int modus;
};