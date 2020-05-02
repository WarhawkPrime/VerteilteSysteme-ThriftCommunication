#include "udp_server.h"
#include <iostream>


int main(int argc, char *argv[]) {

	//Variables
	int portId;
	int a;


	//Check if port exists and is valid
	if (argc < 2) {
		std::cout << "Error! Usage: " << argv[0] << " [port]" << std::endl;
		std::cout << "Use ports between 2000 and 65535!" << std::endl;
		std::cin >> a;
		return 0;
	}

	UDP_server *srvr = new UDP_server();
	bool result = srvr->initialize();

	while (result != R_OK) {
		usleep(5000);
		result = srvr->initialize();
	}


	return 0;
}