#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>	
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <iostream>


int main(int argc, char *argv[]) {

	//Variables
	int portId;


	//Check if port exists and is valid
	if (argc < 2) {
		std::cout << "Error! Usage: server [port]" << std::endl;
		std::cout << "Use ports between 2000 and 65535!" << std::endl;
		return 0;
	}



	return 0;
}