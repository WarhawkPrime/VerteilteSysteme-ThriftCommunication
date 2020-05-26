#include "Skynet.h"

Skynet::Skynet() {

	this->fileHandle = new Telemetry_data();
	this->http = new HTTP_Server(this->fileHandle);
	this->udp = new UDP_server();
	// TO-DO: this->udp = new UDP_Server(this->fileHandle);
}

void Skynet::start_skynet_with_udp() {

	this->udp->initialize();
}

void Skynet::start_skynet_with_http() {
	
	this->http->createConnection();
}

Skynet::~Skynet() {
	delete this->udp;
	delete this->http;
	delete this->fileHandle;
}