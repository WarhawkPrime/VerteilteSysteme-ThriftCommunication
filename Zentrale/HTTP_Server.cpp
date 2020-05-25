#include "HTTP_Server.h"
#include <string.h>

HTTP_Server::HTTP_Server()
{
	this->sockfd = 0;
	this->port = 80;
	this->server_addr.sin_family = AF_UNSPEC;
	this->server_addr.sin_addr.s_addr = INADDR_ANY;
	this->server_addr.sin_port = port;
}


int HTTP_Server::createConnection() {

	// Gather information about connections
	memset(&hints, 0, sizeof(hints)); // struct needs to be empty
	hints.ai_family = AF_UNSPEC; // Either IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // Initialize a stream socket
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	// Specify expected connection types 
	int status = 0;
	struct addrinfo *result;
	const char* p = "80";
	if ((status = getaddrinfo(NULL, p, &hints, &result)) != 0) {
		perror("Getaddrinfo");
		std::cout << "Error! Couldn't populate struct!" << std::endl;
		return 0;
	}

	// Create parent socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket");
		std::cout << "Couldn't open socket!" << std::endl;
		return -1;
	}

	memset(&this->server_addr, 0, sizeof(server_addr));
	// Bind socket
	if ((bind(sockfd, result->ai_addr, result->ai_addrlen)) < 0) {
		perror("Bind");
		std::cout << "Couldn't bind socket!" << std::endl;
		return -1;
	}
	
	// Listen for all incoming connections
	if ((listen(sockfd, 10)) < 0) {
		perror("Listen");
		std::cout << "Couldn't listen to socket!" << std::endl;
		return -1;
	}
		// Accept all incoming connections
		while (1) {

			// Set addr length to size of client_addr
			this->client_addr_length = sizeof(client_addr);
			if ((child_sockfd = accept(sockfd, (struct sockaddr*) &client_addr, &client_addr_length)) < 0) {
				perror("Accept");
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
	
	const int max_req_length = 65536;
	int num_bytes_read = 0;
	int num_bytes_written = 0;
	std::string request;


		memset(&this->readBuffer, 0, MAX_BUFFER);
		if ((num_bytes_read = recv(sockfd, readBuffer, MAX_BUFFER, NULL)) < 0) {
			perror("Read");
			std::cout << "Couldn't read from socket!" << std::endl;
			return -1;
		}
		else {

			std::cout << "Received Bytes: " << num_bytes_read << std::endl;
			request = readBuffer;
		}

		handleRequest(sockfd, request);


	/*
	while ((num_bytes_read = recv(sockfd, readBuffer, MAX_BUFFER, NULL)) != 0) {

		request.append(readBuffer);
	}
	*/

	/*
	if ((num_bytes_read = recv(sockfd, readBuffer, MAX_BUFFER, NULL)) < 0) {
		perror("Read");
		std::cout << "Couldn't read from socket!" << std::endl;
		return -1;
	}
	if (!num_bytes_read == 0) {

		std::cout << "Received Bytes: " << num_bytes_read << std::endl;
		// Print received message
		//readBuffer[num_bytes_read] = '\0';
		std::cout << readBuffer << std::endl;
	}
	else {
		std::cout << "num_bytes_read was 0" << std::endl;
	}

	if ((num_bytes_written = send(sockfd, response, sizeof(response), NULL)) < 0) {
		perror("write");
		std::cout << "Failed to respond!" << std::endl;
		return -1;
	}
	*/
}

// Receives incoming request and fetches data
int HTTP_Server::handleRequest(int sockfd, std::string req) {

	// Variables to store requested information
	std::string lineString, requestedData, requestSave;
	long sensorId;
	requestedData = "Server Test response";
	

	// String manipulation variables
	std::string s, delim = "\r\n";
	int pos, counter = 0;

	if (!req.empty()) {
		// Read all values between \r\n delimiters
		requestSave = req;
		while ((pos = req.find(delim)) != std::string::npos) {

			s = req.substr(0, pos);
			if (s.empty()) {
				std::cout << "s is empty. s: " << s << std::endl;
				counter++;
				std::cout << "counter/c after increment: " << counter << std::endl;
			}
			else {

				std::cout << "Teilstring: " << s << std::endl;
			}
			
			if (counter == 2) {
				std::cout << "req after end of header: " << req << std::endl;
				break;
			}
			
			req.erase(0, pos + delim.length());
		}
		std::cout << "Received Request: " << requestSave << std::endl;
		std::cout << "Body of received request: " << req << std::endl;
	}
	else {
		std::cout << "request was empty" << std::endl;
	}

	// TO-Do: Get sensor data from Telemetry.txt file specified in the received http request and send data back
	sendResponse(sockfd, requestedData);

	return 0;
}

// Sends the HTTP response header with information
int HTTP_Server::sendResponse(int sockfd, std::string data) {
	
	int num_bytes_written = 0;
	std::string response, respCode;
	respCode = "200 ok";
	std::string s_content_length;
	int content_length = 0;
	//HTTP/1.1 200 ok\r\n
	//Content-type: text/html\r\n
	//Content-length: 41\r\n
	//\r\n\r\n
	//Sensor data goes here -> data (aka. body)
	content_length = data.length() + 1;
	s_content_length = std::to_string(content_length);

	response += "HTTP/1.1 " + respCode + "\r\n";
	response += "Content-type: text/html\r\n";
	response += "Content-length: " + s_content_length + "\r\n";
	response += "\r\n\r\n"; //End of response header
	response += data;

	// Send response
	if ((num_bytes_written = send(sockfd, response.c_str(), response.length(), NULL)) < 0) {
		perror("write");
		std::cout << "Failed to respond!" << std::endl;
		return -1;
	}
	else {

		std::cout << "Sent " << num_bytes_written << " bytes to client" << std::endl;
		std::cout << "Successfully sent following data: " << response.c_str() << std::endl;
	}

	return 0;
}
