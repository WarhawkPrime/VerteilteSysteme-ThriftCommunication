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
	//int option = 1;
	//setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

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
	int num_bytes_read = BUF_SIZE;
	int num_bytes_written = 0;

	std::string rec_message;
	memset(readBuffer, 0, BUF_SIZE);

	//TODO: read the recv as long as there are bytes to receive
	while (num_bytes_read == BUF_SIZE) {
		num_bytes_read = recv(sockfd, readBuffer, BUF_SIZE, 0);

		std::cout << "buffer: " << readBuffer << std::endl;

		if (num_bytes_read < 0) {
			perror("Read");
		}

		rec_message += readBuffer;
	}


	//rec_message = readBuffer;
	const char* teminate = "\0";
	rec_message.append(teminate);

	std::cout << rec_message << std::endl;

	return rec_message;
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