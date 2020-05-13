#pragma once

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../Sensoren/Sensor_Management.h"
#include "../Sensoren/Sensor_Management.cpp"

#include "../Sensoren/Sensor.h"
#include "../Sensoren/Sensor.cpp"

#include "../Sensoren/UDP_Socket.h"
#include "../Sensoren/UDP_Socket.cpp"



TEST_CASE("t1") {
	Sensor_Management sm;

	CHECK(sm.firstTest()  == 1);
}