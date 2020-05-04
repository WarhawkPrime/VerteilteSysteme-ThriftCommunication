#include "udp_server.h"
#include <iostream>


int main(int argc, char *argv[]) {

	//Variables
	int portId;
	int a;


	UDP_server *srvr = new UDP_server();
	srvr->initialize();


	return 0;
}