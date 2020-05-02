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

	void userDialog();

	void createTemperatureSensor();
	void createBrightnessSensor();
	void createWindSensor();
	void createHumiditySensor();

	void setSensor(Sensor* newSensor) { this->sensor = newSensor; }
	Sensor* getSensor() { return sensor; }
	
private:
	Sensor *sensor;
};