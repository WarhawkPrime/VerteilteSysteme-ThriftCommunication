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
	hints.ai_protocol = 0;
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

void TCP_Socket::send_msg_to(char* msg)
{
	size_t len;
	int bytes_sent = 0;

	len = strlen(msg);
	const char* m;
	//ssize_t send(int sockfd, const void *buf, size_t len, int flags);
	bytes_sent = sendto(sockfd, msg, len, 0, (struct sockaddr*) & servaddr, addrSize);

	//ssize_t send(int s, const void *msg, size_t len, int flags);
	//ssize_t s = send(sockfd, m, strlen(m), 0);

	if (bytes_sent < 0) {
		perror("Could not connect to socket");
		exit(EXIT_FAILURE);
	}
}

void TCP_Socket::rec_msg_fr()
{
	ssize_t rec = 0;
	char* msg = nullptr;
	size_t len = 0;
	len = strlen(msg);

	//rec = recv(sockfd, msg, len, 0);
	rec = recvfrom(sockfd, msg, len, 0, (struct sockaddr*) & servaddr, &addrSize);

	//do smth with msg...

	std::cout << msg << std::endl;

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

	//freeaddrinfo(res);	//wird nicht länger gebraucht
}