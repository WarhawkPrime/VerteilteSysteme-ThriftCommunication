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
	//bei spezifischer Adresse: AI_PASSIVE entfernen und bei getaddrinfo null durch die gew�nschte adresse ersetzen

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

void TCP_Socket::send_msg_to(char* msg)
{
	size_t len;
	int bytes_sent = 0;

	len = strlen(msg);
	const char* m;
	//ssize_t send(int sockfd, const void *buf, size_t len, int flags);
	//bytes_sent = sendto(sockfd, msg, len, 0, (struct sockaddr*) & servaddr, addrSize);

	//ssize_t t = send(int s, const void *msg, size_t len, int flags);
	send(sockfd, m, strlen(m), 0);

	if (bytes_sent < 0) {
		perror("Could not connect to socket");
		exit(EXIT_FAILURE);
	}
}

std::string TCP_Socket::rec_msg_fr()
{
	ssize_t rec = 0;
	char msg [BUFSIZ];
	size_t len = 0;
	len = strlen(msg);
	int bytesSend = 1;
	std::string complete_message = "";

	//read the buffer until it is empty
	while (bytesSend != 0) {
		bytesSend = recv(sockfd, msg, len, 0);

		if (bytesSend < 0) {
			perror("Could not receive the message");
			exit(EXIT_FAILURE);
		}

		//TO DO -> write the msg to a string to store the data. or file?
		complete_message += msg;
	}
	return complete_message;
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

//unn�tig f�r udp
void TCP_Socket::connect_socket()
{
	if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
		perror("Could not connect to socket");
		exit(EXIT_FAILURE);
	}

	if (rp == NULL) {
		std::cerr << "Could not connect to address" << std::endl;
	}

	//freeaddrinfo(res);	//wird nicht l�nger gebraucht
}