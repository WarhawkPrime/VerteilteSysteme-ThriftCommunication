#pragma once

#include <iostream>

#include "Sensor.h"
#include <memory>
#include <utility>

#include <chrono>


class SensorManagement
{
public:
	SensorManagement();
	~SensorManagement();

	void user_dialog();
	void create_temperatureSensor(int mod);
	void create_brightnessSensor(int mod);
	void create_windSensor(int mod);
	void create_humiditySensor(int mod);

	void set_sensor(Sensor* newSensor) { this->sensor = newSensor; }
	Sensor* get_sensor() { return sensor; }
	
private:
	Sensor *sensor;
	int modus;
};