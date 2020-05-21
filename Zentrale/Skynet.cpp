#include "Skynet.h"

void Skynet::start_skynet_with_udp() {
	this->udp = new UDP_server();
	this->udp->initialize();
}

void Skynet::start_skynet_with_http() {
	this->http = new HTTP_Server();
	this->http->createConnection();
}

Skynet::~Skynet() {
	delete this->udp;
	delete this->http;
}