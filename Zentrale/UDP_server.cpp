#include "UDP_server.h"

// Constructor
UDP_server::UDP_server(FileManagement* fh)
{
	this->sockfd = 0;
	this->status = 0;
	this->srv_name = "localhost";
	this->fileHandle = fh;
	this->unique_id = 0; 
	this->rec_data = false;
}


// Destructor
UDP_server::~UDP_server() {

}

// Return the correct ip address
void* get_address(struct sockaddr* sock_addr) {

	if (sock_addr->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sock_addr)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sock_addr)->sin6_addr);
}


int UDP_server::create_socket() {

	for (temp = results; temp != NULL; temp = temp->ai_next) {

		// Create the socket
		// int socket(int domain, int type, int protocol): Define the type of socket you want and which protocol to use
		// Check if socket for current address can be created
		int option = 1;
		sockfd = socket(temp->ai_family, temp->ai_socktype, temp->ai_protocol);
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
		if (sockfd  == -1)
			continue;

		// Check if bind() works, then continue with next sensor address
		if (bind(sockfd, temp->ai_addr, temp->ai_addrlen) == 0)
			break;

		// Close the file descriptor
		close(sockfd);
	}
}

//TO DO:
/*
Erstelle f�r jeden einzelnen Sensortyp eine eigene Datei, in der dann diese Daten gespeichert werden.
Dazu muss aus der Nachricht der Sensortyp ermittelt werden und dann die entsprechende file erstellt werden
*/
int UDP_server::read_data(char buffer[NI_MAXHOST], char host[MAX_BUFFER]) {

	// Save data
	std::ifstream historyFile;
	std::ofstream outFile;
	std::string lineString;
	std::string filename;

	
	unique_id = fileHandle->getNextLineNumber(filename);


		// Construct string of data to write
		std::string data(buffer, numBytesReceived);
		
		//search string for whitelist
		std::string t = "temp";
		if (data.find(t) != std::string::npos == true) {
			std::cout << "gefunden" << std::endl;
		}
		else {
			std::cout << "not" << std::endl;
		}

		data.insert(0, ";");
		data.insert(0, host);
		data.insert(0, ";");
		data.insert(0, std::to_string(unique_id));
		std::cout << "Received data: " << data << std::endl;
		historyFile.close();

		outFile.open(filename, std::ios::out | std::ios::app);
		if (outFile.is_open())
			outFile << data;
		else
			std::cout << "Couldn't write to file!" << std::endl;
		outFile.close();

	}
	else {
		std::cout << "Error! Couldn't open file." << std::endl;
	}
}




// Handle all incoming telemetry
int UDP_server::processRequests()
{

	create_socket();

	// If temp is empty, all addresses failed
	if (temp == NULL) {

		std::cout << "Error! Couldn't bind to addresses!" << std::endl;
		std::cout << "Exiting....." << std::endl;
		return R_ERR;
	}

	// results is no longer needed here
	freeaddrinfo(results);

	from = &sensors;

	// Execute recvfrom endlessly
	for (;;) {

		address_length = sizeof(struct sockaddr_storage);
		char host[NI_MAXHOST], service[NI_MAXSERV], buffer[MAX_BUFFER];

		// Handle all incoming messages and save them
		if ((numBytesReceived = recvfrom(sockfd, buffer, MAX_BUFFER, 0, (struct sockaddr*) & from, &address_length)) == -1) {
			std::cout << "Failed request." << std::endl;
			continue;
		}


		status = getnameinfo((struct sockaddr*) & from, address_length, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);

		if (status == 0) {
			std::cout << "Received " << numBytesReceived << " bytes from " << host << ":" << service << std::endl;

			if (numBytesReceived >= MAX_BUFFER) {
				std::cout << "Buffer not large enough!" << std::endl;
			}
			else {

				if (buffer == NULL) {
					std::cout << "buffer is NULL" << std::endl;
				}
				else {
					// Terminate received string
					buffer[numBytesReceived] = '\0';

					this->read_data(buffer, host);
				}

			}
		}
		else {
			std::cout << "Error in getnameinfo()!" << std::endl;
		}

	}
	return R_OK;
}



// Get all sensor addresses
int UDP_server::initialize()
{
	memset(&hints, 0, sizeof(hints)); // struct needs to be empty
	hints.ai_family = AF_UNSPEC; // Either IPv4 or IPv6
	hints.ai_socktype = SOCK_DGRAM; // Initialize a datagram socket
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	if ((status = getaddrinfo(NULL, PORT, &hints, &results)) != 0) {

		std::cout << "Error! Couldn't populate struct!" << std::endl;
		// error.log();
		return R_FAIL;

	}

	processRequests();

	return 0;
}