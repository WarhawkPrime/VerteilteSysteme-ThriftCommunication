#include "udp_server.h"


//
UDP_server::UDP_server()
{
	this->sockfd = 0;
	this->status = 0;
	from = &sensors;
	memset(&hints, 0, sizeof(hints)); // struct needs to be empty
}


// Return the ip address
void* get_address(struct sockaddr* sock_addr) {

	if (sock_addr->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sock_addr)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sock_addr)->sin6_addr);
}


// Handle all incoming telemetry
int UDP_server::processRequests()
{

	for (temp = results; temp != NULL; temp = temp->ai_next) {

		// Create the socket
		// int socket(int domain, int type, int protocol): Define the type of socket you want and which protocol to use
		// Check if socket for current address can be created
		if (sockfd = socket(temp->ai_family, temp->ai_socktype, temp->ai_protocol) == -1)
			continue;

			// Check if bind() works, then continue with next sensor address
		if (bind(sockfd, temp->ai_addr, temp->ai_addrlen) == 0)
			break;
			
		// Close the file descriptor
		close(sockfd);

	}

	// If temp is empty, all addresses failed
	if (temp == NULL) {

		std::cout << "Error! Couldn't bind to addresses!" << std::endl;
		std::cout << "Exiting....." << std::endl;
		return R_ERR;
	}

	// results is no longer needed here
	freeaddrinfo(results);


	address_length = sizeof(sensors);
	// Handle all incoming messages and save them
	if ((numBytesReceived = recvfrom(sockfd, buffer, MAX_BUFFER-1, 0, (struct sockaddr*) &from, &address_length)) == -1) {

		std::cout << "Error! recvfrom() failed!" << std::endl;
		return R_ERR;
	}

	printf("Received a packet from %s\n", inet_ntop(from->ss_family, get_address((struct sockaddr*) & from), s, sizeof(s)));
	printf("The packet is %d bytes long\n", numBytesReceived);
	buffer[numBytesReceived] = '\0';

	close(sockfd);

	return R_OK;

}


// Not needed ?
int UDP_server::block()
{


	return R_OK;
}


// Get all sensor addresses
int UDP_server::initialize()
{
	hints.ai_family = AF_INET; // IPv4
	hints.ai_socktype = SOCK_DGRAM; // Initialize a datagram socket
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = IPPROTO_UDP;

	if ((status = getaddrinfo(NULL, PORT, &hints, &results)) != 0) {
		
		std::cout << "Error! Couldn't populate struct!" << std::endl;
		// error.log();
		return R_FAIL;

	}


	return processRequests();
}
