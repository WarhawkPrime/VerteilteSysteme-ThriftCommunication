#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../Sensoren/Sensor_Management.h"
#include "../Sensoren/Sensor_Management.cpp"
#include "../Sensoren/Sensor.h"
#include "../Sensoren/Sensor.cpp"
#include "../Sensoren/UDP_Socket.h"
#include "../Sensoren/UDP_Socket.cpp"
#include "../Zentrale/UDP_server.h"
#include "../Zentrale/UDP_server.cpp"
#include "../Zentrale/FileManagement.h"
#include "../Zentrale/FileManagement.cpp"
#include "../Zentrale/HTTP_Server.h"
#include "../Zentrale/HTTP_Server.cpp"
#include "../thriftServer/SendSensordataService.h"
#include "../thriftServer/ServerFileManagement.h"
#include "../thriftServer/verbindung_constants.h"
#include "../thriftServer/verbindung_types.h"
#include "../thriftServer/SendSensordataService.cpp"
#include "../thriftServer/ServerFileManagement.cpp"
#include "../thriftServer/verbindung_constants.cpp"
#include "../thriftServer/verbindung_types.cpp"
#include "../thriftServer/SendSensordataService_server.skeleton.cpp"
#include "../thriftServer/ThriftClient.h"
#include "../thriftServer/ThriftClient.cpp"

#include "../Client/Client.h"
#include "../Client/Client.cpp"
#include "../Client/TCP_Socket.h"
#include "../Client/TCP_Socket.cpp"


using namespace std;
using namespace std::chrono;


UDP_server* udp;
HTTP_Server* http;
FileManagement* fileHandle;
//ThriftClient* tc;


void doTest(bool rec_data) {
	CHECK(rec_data == true);
};

void i() {
	fileHandle = new FileManagement();
	udp = new UDP_server(fileHandle);
	http = new HTTP_Server(fileHandle);
}

TEST_SUITE("Tests für Funktionale und Nichtfunktionale Anforderungen mit der Zentrale am laufen" * doctest::description("Test mit Zentrale")) 
{
	

	TEST_CASE("Start der Zentrale")
	{
		i();

		//Anforderungen, deren Umsetzung direkt der Zweckbestimmung des Produkts dienen
		SUBCASE("Funktionale Tests")
		{
			SUBCASE("Kommt die Nachricht an der Zentrale an") {
				Sensor_Management sm;
				sm.create_temperatureSensor(0, "8");

				CHECK(udp->get_statusVar() == 0);
			}

			SUBCASE("HTTP REQUEST and RESPONSE") {
				Client c;

				std::string a = "=";
				std::string sPara = "param1";
				sPara += a + "0";

				c.build_header("temp.txt", sPara);

				//c.build_header("temp.txt", 0);
				c.rec_message();
				c.interprete_message();
				CHECK(c.getResponse().message != "");
			}

			SUBCASE("Thrift Message") {

				ThriftClient t;

				CHECK(t.startThrift() == true);

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

					sm.create_temperatureSensor(0, "8");
					if (udp->get_statusVar() == 0) {
						counter++;
					}
					sm.create_brightnessSensor(0, "8");
					if (udp->get_statusVar() == 0) {
						counter ++;
					}
					sm.create_humiditySensor(0, "8");
					if (udp->get_statusVar() == 0) {
						counter ++;
					}
					sm.create_windSensor(0, "8");
					if (udp->get_statusVar() == 0) {
						counter ++;
					}
				}
				CHECK(counter >= (1000 - 10));
			}

			SUBCASE("Stabiles gleichzeitiges Senden") {
				//nichtfunktionale
				//zeit, umgebungsbedingung, performance

					Sensor_Management sm;
					sm.create_temperatureSensor(0, "8");

					Client c;
					std::string a = "=";
					std::string sPara = "param1";
					sPara += a + "0";

					c.build_header("temp.txt", sPara);
					c.rec_message();
					c.interprete_message();


					bool t1;
					bool t2;
					if (c.getResponse().message != "") {
						t1 = true;
					}
					else {
						t1 = false;
					}

					if (udp->get_statusVar() == 0) {
						t2 = true;
					}
					else {
						t2 = false;
					}

					CHECK(t1 == true);
					CHECK(t2 == true);
			}

			SUBCASE("thrift Dauer") {

				ThriftClient t;
				auto start = high_resolution_clock::now();

				for (int i = 0; i < 10; i++ ) {
					t.startThrift();
				}

				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);

				CHECK(duration.count() < 1000000 );
			}

		}
	}
}