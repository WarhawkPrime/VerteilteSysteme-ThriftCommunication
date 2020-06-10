#include "Skynet.h"

Skynet::Skynet() {

	this->fileHandle = new FileManagement();
	this->http = new HTTP_Server(this->fileHandle);
	this->udp = new UDP_server(this->fileHandle);
}

void Skynet::start_skynet_with_udp() {

	this->udp->initialize();
}

void Skynet::start_skynet_with_http() {
	
	this->http->createConnection();
}

void Skynet::start_skynet_with_thrift() {
	std::cout << "start with thrift" << std::endl;
}

Skynet::~Skynet() {
	delete this->udp;
	delete this->http;
	delete this->fileHandle;
}