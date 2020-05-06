#pragma once
#include <errno.h>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#include "telemetry_data.h"
#include <fstream>
#include <sstream>

#define MAX_BUFFER 1024
#define PORT "40000"
#define R_OK 10
#define R_FAIL 20
#define R_ERR 30
#define R_RETURN 40

// Class that contains all server functionality to send and receive data from the sensors
class UDP_server {

	// Variables
	private: 
		int sockfd; // Socket File Descriptor
		int status; 
		int numBytesReceived;
		struct addrinfo hints, *results, *temp; // Contains a linked list of results 
		struct sockaddr_storage sensors, *from; // Struct for IP addresses and ports of sensors
		socklen_t address_length; // address length required for recvfrom()
		int destfd; // Filedescriptor to save the received data
		char s[INET6_ADDRSTRLEN];
		char* srv_name;
		TelemetryData* data;
		long unique_id;

	public:
		// Server functions
		UDP_server(); 
		~UDP_server();
		int processRequests();
		int initialize(); // Initialize server

};