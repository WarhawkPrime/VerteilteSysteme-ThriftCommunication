#pragma once

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../Sensoren/Sensor_Management.h"
#include "../Sensoren/Sensor_Management.cpp"
#include "../Sensoren/Sensor.h"
#include "../Sensoren/Sensor.cpp"
#include "../Sensoren/UDP_Socket.h"
#include "../Sensoren/UDP_Socket.cpp"

#include "../Zentrale/UDP_server.h"
#include "../Zentrale/Telemetry_data.h"
#include "../Zentrale/UDP_server.cpp"
#include "../Zentrale/Telemetry_data.cpp"


void doTest(bool rec_data) {
	CHECK(rec_data == true);
};



TEST_SUITE("Tests für Funktionale und Nichtfunktionale Anforderungen mit der Zentrale am laufen" * doctest::description("Test mit Zentrale")) 
{
	UDP_server udps;

	TEST_CASE("Start der Zentrale")
	{
		udps.initialize();

		//Anforderungen, deren Umsetzung direkt der Zweckbestimmung des Produkts dienen
		SUBCASE("Funktionale Tests")
		{

			SUBCASE("Kommt die Nachricht an der Zentrale an")
			{
				Sensor_Management sm;
				sm.create_temperatureSensor(0);

				CHECK(udps.get_statusVar() == 0);
			}
		} 

		//Anforderungen, die unspezifisch für das Programm sind und die Qualität der Funktionalen Anforderungen überprüft
		SUBCASE("Nichtfunktionale Tests")
		{
			SUBCASE("Paketverlust 1 %")
			{
				int counter;
				for (size_t i = 0; i < 250; i++)
				{
					Sensor_Management sm;

					sm.create_temperatureSensor(0);
					if (udps.get_statusVar() == 0) {
						counter++;
					}
					sm.create_brightnessSensor(0);
					if (udps.get_statusVar() == 0) {
						counter ++;
					}
					sm.create_humiditySensor(0);
					if (udps.get_statusVar() == 0) {
						counter ++;
					}
					sm.create_windSensor(0);
					if (udps.get_statusVar() == 0) {
						counter ++;
					}
				}
				CHECK(counter >= (1000 - 10));
			}
		}
	}

}