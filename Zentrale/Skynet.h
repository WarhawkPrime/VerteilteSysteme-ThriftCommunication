#pragma once

#include "UDP_server.h"
#include "HTTP_Server.h"
#include "ThriftServer.h"
#include "MQTT_Server.h"

#include <thread>


class Skynet
{
public:
	Skynet();
	~Skynet();
	//TO DO => evtl mit template ersetzen oder die beiden Sockets von einer Generalisierung erben lassen
	void start_skynet_with_udp();
	void start_skynet_with_http();
	int start_skynet_with_thrift();
	void start_skynet_with_mqtt();

private:
	UDP_server *udp;
	HTTP_Server *http;
	MQTT_Server *mqtt;
	FileManagement* fileHandle;
	SendSensordataServiceHandler* sh;
	
};