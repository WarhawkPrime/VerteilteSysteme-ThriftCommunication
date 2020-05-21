#include "Skynet.h"

void Skynet::start_skynet_with_udp() {
	udp.initialize();
}

void Skynet::start_skynet_with_http() {
	http.createConnection();
}