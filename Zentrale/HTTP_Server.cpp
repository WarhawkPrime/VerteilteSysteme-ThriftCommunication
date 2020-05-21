#include "HTTP_Server.h"
#include <string.h>

HTTP_Server::HTTP_Server()
{
	
	this->sockfd = 0;
	this->port = 80;
	this->client_addr_length = sizeof(struct sockaddr_in);
	memset(&this->server_addr, 0, sizeof(struct sockaddr_in));
	memset(&this->readBuffer, 0, MAX_BUFFER);
	this->server_addr.sin_family = AF_INET;
	this->server_addr.sin_addr.s_addr = INADDR_ANY;
	this->server_addr.sin_port = 80;
}


int HTTP_Server::createConnection() {

	// Create parent socket
	if (sockfd = socket(AF_INET, SOCK_STREAM, 0) < 0) {
		std::cout << "Couldn't open socket!" << std::endl;
		return -1;
	}

	// Bind socket
	if (bind(sockfd, (struct sockaddr*) & server_addr, sizeof(server_addr)) < 0) {
		std::cout << "Couldn't bind socket!" << std::endl;
		return -1;
	}
	
	// Listen for all incoming connections
	if (listen(sockfd, 10) < 0) {
		std::cout << "Couldn't listen to socket!" << std::endl;
		return -1;
	}
		// Accept all incoming connections
		while (1) {

			if (child_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_length) < 0) {
				std::cout << "Connection attempt failed!" << std::endl;
			}

			// Fork a child process to handle new connection
			pid = fork();
			if (pid < 0) {
				std::cout << "Failed to create child process!" << std::endl;
			}

			// Child
			if (pid == 0) {
				std::cout << "Process started" << std::endl;
				close(sockfd);
				handleConnection(child_sockfd);
				exit(0);
			}
			else {
				// Parent
				close(child_sockfd);
			}
		}
}

// Receive HTTP GET requests
int HTTP_Server::handleConnection(int sockfd) {

	int num_bytes_read = 0;
	int num_bytes_written = 0;
	char* response = "Test response";
	
	if (num_bytes_read = read(sockfd, readBuffer, MAX_BUFFER) < 0) {
		std::cout << "Couldn't read from socket!" << std::endl;
		return -1;
	}
	std::cout << "Received Bytes: " << num_bytes_read << std::endl;
	// Print received message
	readBuffer[num_bytes_read] = '\0';
	//std::cout << readBuffer << std::endl;

	if (num_bytes_written = write(sockfd, response, sizeof(response)) < 0) {
		std::cout << "Failed to respond!" << std::endl;
		return -1;
	}

}
