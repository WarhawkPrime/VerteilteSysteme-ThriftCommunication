#include "Skynet.h"

void Skynet::start_skynet_with_udp() {
	udp = new UDP_server();
	udp->initialize();
}

void Skynet::start_skynet_with_http() {
	http = new HTTP_Server();
	http->createConnection();
}

Skynet::~Skynet() {
	delete udp;
	delete http;
}