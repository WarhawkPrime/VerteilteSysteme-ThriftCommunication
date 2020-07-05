#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../Sensoren/Sensor_Management.h"
#include "../Sensoren/Sensor_Management.cpp"
#include "../Sensoren/Sensor.h"
#include "../Sensoren/Sensor.cpp"
#include "../Sensoren/UDP_Socket.h"
#include "../Sensoren/UDP_Socket.cpp"
#include "../Sensoren/MQTT_Sensor.h"
#include "../Sensoren/MQTT_Sensor.cpp"
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


//void doTest(bool rec_data) {
//	CHECK(rec_data == true);
//};

void i() {
	fileHandle = new FileManagement();
	udp = new UDP_server(fileHandle);
	http = new HTTP_Server(fileHandle);

}

TEST_SUITE("Tests f�r Funktionale und Nichtfunktionale Anforderungen mit der Zentrale am laufen" * doctest::description("Test mit Zentrale")) 
	{
	

		TEST_CASE("Start der Zentrale")
		{
			i();

			//Anforderungen, deren Umsetzung direkt der Zweckbestimmung des Produkts dienen
			SUBCASE("Funktionale Tests")
			{
				/*
				SUBCASE("Kommt die Nachricht an der Zentrale an") {
					Sensor_Management sm;
					sm.create_temperatureSensor(0, "8");

					CHECK(udp->get_statusVar() == 0);
				}
				*/

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

				SUBCASE("MQTT") {

					//Sensor_Management sm;
					//sm.create_windMQTTSensor(0, "8");
					//sm.get_mqttSensor()->repeater(0,8,0);
					MQTT_Sensor* ms = new MQTT_Sensor(0,"8");
					
					CHECK(ms->repeater(0,8,0, "windsensor");				
				}




			} 

			//Anforderungen, die unspezifisch f�r das Programm sind und die Qualit�t der Funktionalen Anforderungen �berpr�ft
			SUBCASE("Nichtfunktionale Tests")
			{
				/*
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
				*/
				
				
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

	
				SUBCASE("MQTT Quality") {
				
				// create multiple Sensors and every Sensor should send multiple data records.
				// the Server should ensure, that every message is at least once received
				
					int sensorDataCount = 10;
				
					MQTT_Sensor* st = new MQTT_Sensor(0,"8");
					MQTT_Sensor* sl = new MQTT_Sensor(0,"16");
					MQTT_Sensor* sw = new MQTT_Sensor(0,"32");
					MQTT_Sensor* sh = new MQTT_Sensor(0,"64");
					
					
					bool checkBool = true;
					//insgesamt 40 Nachrichten werden gesendet
					
					auto start = high_resolution_clock::now();
					
						for(int c = 0; c <= sensorDataCount; c++;) {
							
								if(st->repeater(0,8,0, "temperatursensor") ==  false) {
										checkBool = false;
								} 
								if(s1->repeater(0,16,0, "helligkeitssensor") == false) {
										checkBool = false;
								}
								if(sw->repeater(0,32,0, "windsensor") == false) {
										checkBool = false;
								}
								if(sh->repeater(0,64,0, "luftfeuchtigkeitssensor") == false) {
										checkBool = false;
								}
						}
					
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					
					CHECK(duration.count() < 1000000 );
					CHECK(checkBool == true);
					
				}
		
			}
		}
	}
	
	
	
	
	
	
	