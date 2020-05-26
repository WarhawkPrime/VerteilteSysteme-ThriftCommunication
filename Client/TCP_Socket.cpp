#include "TCP_Socket.h"

TCP_Socket::TCP_Socket() {

}

TCP_Socket::~TCP_Socket() {

}

void TCP_Socket::fill_serverInfo()
{
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_UNSPEC;			//ipv4 or ipv6
	hints.ai_socktype = SOCK_STREAM;		//stream (tcp) socket
	hints.ai_flags = AI_PASSIVE;			//bind to ip of the host the programm is running on
	hints.ai_protocol = IPPROTO_TCP;
	//bei spezifischer Adresse: AI_PASSIVE entfernen und bei getaddrinfo null durch die gewünschte adresse ersetzen

	getaddrinfo(NULL, CPORT, &hints, &res);
	rp = res;

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(IPORT);		//stores numbers in memory in Network byte order -> most significant byte first (big endian)
	servaddr.sin_addr.s_addr = INADDR_ANY;

	memset(servaddr.sin_zero, 0, sizeof(servaddr.sin_zero));
	addrSize = sizeof(servaddr);
}

void TCP_Socket::create_socket()
{
	//int socket(int domain, int type, int protocol); -> -1 on error
	sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);	//sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 

	if (sockfd < 0) {
		perror("Could not create socket");
		exit(EXIT_FAILURE);
	}
}

void TCP_Socket::send_msg_to(const char* msg)
{
	size_t len;
	int bytes_sent = 0;

	len = strlen(msg);
	
	//const char* m;
	//ssize_t send(int sockfd, const void *buf, size_t len, int flags);
	//bytes_sent = sendto(sockfd, msg, len, 0, (struct sockaddr*) & servaddr, addrSize);

	//ssize_t t = send(int s, const void *msg, size_t len, int flags);

	bytes_sent = send(sockfd, msg, strlen(msg), 0);

	if (bytes_sent < 0) {
		perror("Could not connect to socket");
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << std::endl;
		std::cout << "Sent " << bytes_sent << " bytes to server!" << std::endl;
	}
}

std::string TCP_Socket::rec_msg_fr()
{
	
	char readBuffer[BUF_SIZE];
	int num_bytes_read = 0;
	int num_bytes_written = 0;

	std::string rec_message;

	//char* response = "Server Test response\0";
	memset(readBuffer, 0, BUF_SIZE);

	while ((num_bytes_read = recv(sockfd, readBuffer, BUF_SIZE, NULL)) != 0) {
		rec_message.append(readBuffer);
	}

	const char* teminate = "\0";
	rec_message.append(teminate);
	return rec_message;
	

	/*
	if ((num_bytes_read = recv(sockfd, readBuffer, BUF_SIZE, NULL)) < 0) {
		perror("Read");
		std::cout << "Couldn't read from socket!" << std::endl;
		return "-1";
	}
	if (!(num_bytes_read == 0)) {

		std::cout << "Received Bytes: " << num_bytes_read << std::endl;
		// Print received message
		readBuffer[num_bytes_read] = '\0';
		std::cout << readBuffer << std::endl;
		return readBuffer;
	}
	else {
		std::cout << "num_bytes_read was 0" << std::endl;
	}
	*/
	
	/*
	if ((num_bytes_written = send(sockfd, response, sizeof(response), NULL)) < 0) {
		perror("write");
		std::cout << "Failed to respond!" << std::endl;
		return "-1";
	}
	*/

	/*
	ssize_t rec = 0;
	char msg [BUF_SIZE];
	size_t len = 0;
	len = strlen(msg);
	int bytesSend = 1;
	std::string complete_message = "";

	//read the buffer until it is empty
	//while (bytesSend != 0) {
		bytesSend = recv(sockfd, msg, len, 0);

		if (bytesSend < 0) {
			perror("Could not receive the message");
			exit(EXIT_FAILURE);
		}

		std::cout << msg << std::endl;

		//TO DO -> write the msg to a string to store the data. or file?
		complete_message += msg;
	//}
	return complete_message;
	*/

	/*
	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	if (n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s
	",buffer);
	*/
	//rec = recvfrom(sockfd, msg, len, 0, (struct sockaddr*) & servaddr, &addrSize);

	//do smth with msg...
}

void TCP_Socket::close_socket()
{
	int c = 0;

	c = close(sockfd);

	if (c < 0) {
		perror("Could not close socket");
		exit(EXIT_FAILURE);
	}
}

//unnötig für udp
void TCP_Socket::connect_socket()
{
	if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
		perror("Could not connect to socket");
		exit(EXIT_FAILURE);
	}

	if (rp == NULL) {
		std::cerr << "Could not connect to address" << std::endl;
	}
}