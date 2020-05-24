#include "UDP_Socket.h"

UDP_Socket::UDP_Socket()
{

}

UDP_Socket::~UDP_Socket()
{

}

void UDP_Socket::fill_serverInfo()
{
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_UNSPEC;			//ipv4 or ipv6
	hints.ai_socktype = SOCK_DGRAM;		//datagram (udp) socket
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

	std::cout << servaddr.sin_addr.s_addr << std::endl;

}


void UDP_Socket::create_socket()
{
	//int socket(int domain, int type, int protocol); -> -1 on error
	sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);	//sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 

	if (sockfd < 0) {
		perror("Could not create socket");
		exit(EXIT_FAILURE);
	}
}


void UDP_Socket::bind_socket()
{
	int b = 0;
	//int bind(ind fd, struct sockaddr *local_addr, socklen_t addr_lenght); -> 0 on success, -1 on error
	b = bind(sockfd, res->ai_addr, res->ai_addrlen);

	if (b < 0) {
		perror("Could not bind the socket");
		exit(EXIT_FAILURE);
	}
}



void UDP_Socket::send_msg_to(char* msg)
{
	size_t len;
	int bytes_sent = 0;

	len = strlen(msg);

	bytes_sent = send(sockfd, msg, len, 0);
	//bytes_sent = sendto(sockfd, msg, len, 0, (struct sockaddr*) & servaddr, addrSize);

	msg = NULL;

	if (bytes_sent < 0) {
		perror("Could not connect to socket");
		exit(EXIT_FAILURE);
	}
}

void UDP_Socket::rec_msg_fr()
{

}

void UDP_Socket::close_socket()
{
	int c = 0;

	c = close(sockfd);

	if (c < 0) {
		perror("Could not close socket");
		exit(EXIT_FAILURE);
	}
}


//unnötig für udp
void UDP_Socket::connect_socket()
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