#include "Client.h"

Client::Client() {
	tcp.fill_serverInfo();
	tcp.create_socket();
	tcp.connect_socket();
	sendMessage();
	recMessage();
}

Client::~Client() {
	tcp.close_socket();
}

void Client::buildHeader() {

}

void Client::sendMessage() {

	char* msg = "Hallo";

	tcp.send_msg_to(msg);
}

void Client::recMessage() {

	tcp.rec_msg_fr();

}