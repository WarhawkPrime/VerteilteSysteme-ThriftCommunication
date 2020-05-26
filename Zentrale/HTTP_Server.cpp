#include "HTTP_Server.h"
#include <string.h>



HTTP_Server::HTTP_Server(FileManagement* fh)
{
	this->BAD_REQUEST = false;
	this->sockfd = 0;
	this->port = 80;
	this->server_addr.sin_family = AF_UNSPEC;
	this->server_addr.sin_addr.s_addr = INADDR_ANY;
	this->server_addr.sin_port = port;
	this->fileHandle = fh;

}

HTTP_Server::~HTTP_Server() {

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
		std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
		std::cout << "Error! Couldn't populate struct!" << std::endl;
		std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
		return 0;
	}

	// Create parent socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket");
		std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
		std::cout << "Couldn't open socket!" << std::endl;
		std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
		return -1;
	}

	
	// Bind socket
	memset(&this->server_addr, 0, sizeof(server_addr));
	if ((bind(sockfd, result->ai_addr, result->ai_addrlen)) < 0) {
		perror("Bind");
		std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
		std::cout << "Couldn't bind socket!" << std::endl;
		std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
		return -1;
	}
	
	// Listen for all incoming connections
	if ((listen(sockfd, 10)) < 0) {
		perror("Listen");
		std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
		std::cout << "Couldn't listen to socket!" << std::endl;
		std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
		return -1;
	}
		// Accept all incoming connections
		while (1) {

			// Set addr length to size of client_addr
			this->client_addr_length = sizeof(client_addr);
			if ((child_sockfd = accept(sockfd, (struct sockaddr*) &client_addr, &client_addr_length)) < 0) {
				perror("Accept");
				std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
				std::cout << "Connection attempt failed!" << std::endl;
				std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
			}

			// Fork a child process to handle new connection
			pid = fork();
			if (pid < 0) {
				std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
				std::cout << "Failed to create child process!" << std::endl;
				std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
			}

			// Child
			if (pid == 0) {
				std::cout << ">------------------------------------------------------------------------<" << std::endl;
				std::cout << "Process started" << std::endl;
				std::cout << ">------------------------------------------------------------------------<" << std::endl;
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
	std::string request;


		memset(&this->readBuffer, 0, MAX_BUFFER);
		if ((num_bytes_read = recv(sockfd, readBuffer, MAX_BUFFER, NULL)) < 0) {
			perror("Read");
			std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
			std::cout << "Couldn't read from socket!" << std::endl;
			std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
			return -1;
		}
		else {
			std::cout << ">------------------------------------------------------------------------<" << std::endl;
			std::cout << "Received a request of " << num_bytes_read << " Bytes! " << std::endl;
			std::cout << ">------------------------------------------------------------------------<" << std::endl;
			request = readBuffer;
			return handleRequest(sockfd, request);
		}

		return -1;
}

// Receives incoming request and fetches data, drops connection if given connection: close
int HTTP_Server::handleRequest(int sockfd, std::string req) {

	// Variables to store requested information
	std::string requestSave;
	std::vector<std::string>* requestParamVector = new std::vector<std::string>();

	// String manipulation variables
	std::string s, delim = "\r\n";
	int pos, counter = 0;

	if (!req.empty()) {
		// Read all values between \r\n delimiters
		requestSave = req;
		while ((pos = req.find(delim)) != std::string::npos) {

			s = req.substr(0, pos);
			if (s.empty()) {

				counter++;
			}
			else {

				requestParamVector->push_back(s);
			}
			
			if (counter == 2) {

				break;
			}
			
			req.erase(0, pos + delim.length());
		}
		

		// Get requested sensor data
		request r;
		std::string* data = fetchRequestedData(requestParamVector, r);
		
		std::string response = createResponse(data, r);

		return sendResponse(sockfd, response);
	}
	else {
		std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
		std::cout << "Request was empty!" << std::endl;
		std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
		return -1;
	}
}

std::string* HTTP_Server::fetchRequestedData(std::vector<std::string>* params, request& r) {

	std::string* data = new std::string();
	REQUEST e_r;

	// Set struct members
	std::string type = ":", get = "GET";
	int counter = 0;
	for (int i = 0; i < params->size(); i++) {

		std::string tmp = params->at(i);
		tmp.erase(std::remove_if(tmp.begin(), tmp.end(), isspace), tmp.end());
		int p = tmp.find(type);
		
		if (p == std::string::npos) {
			*data = "Bad Request!";
			BAD_REQUEST = true;
			return data;
		}
			

		switch (counter) {

			case REQ: {
				int pos = tmp.find(get);
				if (pos != std::string::npos) {

					tmp = tmp.substr(pos + get.size(), std::string::npos);
					r.req = tmp;
					counter++;
				}
				break;
			}
			case HOST: {
				
				tmp = tmp.substr(p + type.size(), std::string::npos);
				r.host = tmp;
				counter++;
				break;
			}
			case CACHE: {

				tmp = tmp.substr(p + type.size(), std::string::npos);
				r.cache = tmp;
				counter++;
				break;
			}
			case DNT: {

				tmp = tmp.substr(p + type.size(), std::string::npos);
				r.dnt = tmp;
				counter++;
				break;
			}
			case ACCEPT: {

				tmp = tmp.substr(p + type.size(), std::string::npos);
				r.accept = tmp;
				counter++;
				break;
			}
			case ACCEPT_CHARSET: {

				tmp = tmp.substr(p + type.size(), std::string::npos);
				r.accept_charset = tmp;
				counter++;
				break;
			}
			case CONNECTION: {

				tmp = tmp.substr(p + type.size(), std::string::npos);
				r.connection = tmp;
				counter++;
				break;
			}
			default: {
				*data = "Bad Request!";
				BAD_REQUEST = true;
				return data;
				break;
			}
		}
	}

	// Retrieve file parameters and file to read from
	std::string delim, param1, value1, path, host, prefix, a, s = r.req;
	std::vector<std::string> fileLines;
	delim = ":";
	int count = 0;
	int pos = 0;

	if (!s.empty()) {

		std::cout << "s: " << s << std::endl;

		while ((pos = s.find(delim)) != std::string::npos) {

			a = s.substr(0, pos);

			if (count == 0) {

				prefix = a;
				std::cout << "prefix: " << prefix << std::endl;
				s.erase(0, pos + delim.length());
				count++;
			}
			else if (count == 1) {

				host = a;
				std::cout << "host: " << host << std::endl;
				s.erase(0, pos + delim.length());
				count++;
			}
			else {
				break;
			}
		}
	
		param1 = s;
		std::cout << "param1: " << param1 << std::endl;
		param1.erase(0, 2);
		pos = param1.find("?");
		path = param1.substr(0, pos);
		param1.erase(0, pos + 1);
		std::cout << "path: " << path << std::endl;
		pos = param1.find("=");
		value1 = param1.substr(pos + 1, std::string::npos);
		std::cout << "value1: " << value1 << std::endl;

		if (std::atoi(value1.c_str()) == 0) {

			*data = fileHandle->readLineFromFile(path, 0, false);
		}
		else if (std::atoi(value1.c_str()) == 1) {

			*data = fileHandle->readLineFromFile(path, 0, true);
		}
		else if (std::atoi(value1.c_str()) == 2) {

			fileLines = fileHandle->readFile(path);

			for (int i = 0; i < fileLines.size(); i++)
			{
				*data += fileLines.at(i);
			}
		}
		else {
			std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
			std::cout << "Given Parameter is invalid!" << std::endl;
			std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
			*data = "Bad Request!";
			BAD_REQUEST = true;
			return data;
		}
		
		return data;
	}
	else {
		std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
		std::cout << "Field req of struct REQUEST is empty!" << std::endl;
		std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
		*data = "Bad Request!";
		BAD_REQUEST = true;
		return data;
	}
}

std::string HTTP_Server::createResponse(std::string* data, request &params) {
	
	// Variables
	std::string response;

	// Check if request was valid, if not send back error
	if (!BAD_REQUEST) {

		// Build response
		response += "HTTP/1.1 200 ok \r\n";
		response += "Content-type: text/html\r\n";
		response += "Content-length: " + std::to_string((*data).length()) + "\r\n";
		response += "Connection: " + params.connection + "\r\n";
		response += "\r\n\r\n"; //End of response header
		response += *data;

	}
	else {
		
		// Build response and reset BAD_REQUEST
		response += "HTTP/1.1 400 Bad Request \r\n";
		response += "Content-type: text/html\r\n";
		response += "Content-length: " + std::to_string((*data).length()) + "\r\n";
		response += "Connection: close \r\n";
		response += "\r\n\r\n"; //End of response header
		response += *data;
		BAD_REQUEST = false;
	}

	return response;
}



// Sends the HTTP response header with information
//HTTP/1.1 200 ok\r\n
//Content-type: text/html\r\n
//Content-length: 41\r\n
//Connection: keep-alive
//\r\n\r\n
//Sensor data goes here -> data (aka. body)
int HTTP_Server::sendResponse(int sockfd, std::string response) {
	
	int num_bytes_written = 0;
	
	// Send response
	if ((num_bytes_written = send(sockfd, response.c_str(), response.length(), NULL)) < 0) {

		perror("write");
		std::cout << "Failed to respond!" << std::endl;
		return -1;
	}
	else {

		std::cout << ">------------------------------------------------------------------------<" << std::endl;
		std::cout << "Sent " << num_bytes_written << " bytes to client" << std::endl;
		std::cout << ">------------------------------------------------------------------------<" << std::endl;
		std::cout << "Successfully sent following data: " << std::endl << response.c_str() << std::endl;
		std::cout << ">------------------------------------------------------------------------<" << std::endl;
		return 0;
	}
}
