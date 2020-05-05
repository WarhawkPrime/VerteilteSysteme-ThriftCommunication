#include "udp_server.h"
#include <iostream>


int main(int argc, char *argv[]) {

	// Start server
	UDP_server *srvr = new UDP_server();
	srvr->initialize();

	return 0;
}