#pragma once
#include <errno.h>
#include <string.h>
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

#define MAX_BUFFER 1024
#define PORT "40000"

// Class that contains all server functionality to send and receive data from the sensors
class UDP_server {

	// Variables
	private: 
		int sockfd; // Socket File Descriptor
		int status; 
		int numBytesReceived;
		struct addrinfo hints, *results, *temp; // Contains a linked list of results 
		struct sockaddr_storage sensors, *from; // Struct for IP addresses and ports of sensors
		char buffer[MAX_BUFFER]; // Message buffer
		socklen_t address_length; // address length required for recvfrom()
		char* msg; // Required?
		int destfd; // Filedescriptor to save the received data
		char s[INET6_ADDRSTRLEN];
		

	public:
	// Server functions
		UDP_server(); // Initialize server
		int processRequests();
		int block();
		int initialize();



};