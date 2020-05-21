#include "Client.h"

Client::Client() {
	tcp.fill_serverInfo();
	tcp.create_socket();
	tcp.connect_socket();
}

Client::~Client() {
	tcp.close_socket();
}

void Client::start() {
	sendMessage();
	recMessage();
}


void Client::buildHeader() {

}

void Client::sendMessage() {

	char* msg = "Hallo";

	tcp.send_msg_to(msg);

	std::cout << msg << "send" << std::endl;
}

void Client::recMessage() {

	tcp.rec_msg_fr();

}