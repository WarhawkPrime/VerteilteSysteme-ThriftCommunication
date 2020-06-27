#pragma once

/*
Create a client object
set the options to connect to an MQTT server
set up callback functions
connect the client to an MQTT server
subscribe to any topics the client needs to receive
Repeat until finished:
	Publish any messages the client needs to
	Handle any incoming
disconnect the client
free any memory being used by the client
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <cstring>
#include "mqtt/async_client.h"

#include ""

using namespace std;

class MQTT_Client {

	public:
		
		MQTT_Client() {}
		~MQTT_Client() {}




		private:


};
