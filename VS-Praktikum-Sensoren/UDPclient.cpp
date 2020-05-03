#include "UDPclient.h"

UDPclient::UDPclient()
{

}

UDPclient::~UDPclient()
{

}

void UDPclient::fillServerInfo()
{
	memset(&hints, 0, sizeof (struct addrinfo));

	hints.ai_family = AF_UNSPEC;			//ipv4 or ipv6
	hints.ai_socktype = SOCK_DGRAM;		//datagram (udp) socket
	hints.ai_flags = AI_PASSIVE;			//bind to ip of the host the programm is running on
	hints.ai_protocol = IPPROTO_UDP;
	//bei spezifischer Adresse: AI_PASSIVE entfernen und bei getaddrinfo null durch die gewünschte adresse ersetzen

	getaddrinfo(NULL, CPORT, &hints, &res);
}


void UDPclient::createSocket()
{
	for (rp = res; rp != NULL; rp = rp->ai_next) {

		sockfd =  socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);	//sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 

	}

	if (sockfd < 0) {
		perror("Could not create socket");
		exit(EXIT_FAILURE);
	}
}

//unnötig für client
void UDPclient::bindSocket()
{
	bind(sockfd, res->ai_addr, res->ai_addrlen);

	if (bind < 0) {
		perror("Could not bind the socket");
		exit(EXIT_FAILURE);
	}
}

void UDPclient::connectSocket()
{
	if ( connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1)

	if (connect < 0) {
		perror("Could not connect to socket");
		exit(EXIT_FAILURE);
	}

	if (rp == NULL) {
		std::cerr << "Could not connect to address" << std::endl;
	}

	freeaddrinfo(res);	//wird nicht länger gebraucht
}


void UDPclient::sendMsgTo()
{
	char *msg = "Hello World from the other side";
	int len;
	int bytes_sent;

	len = strlen(msg);

	//int send(int sockfd, const void *msg, int len, int flags);
	//bytes_sent = send(sockfd, msg, len, 0);

	memset(&to, 0, sizeof(to));

	to.sin_family = AF_UNSPEC;
	to.sin_port = htons(IPORT);
	to.sin_addr.s_addr = INADDR_ANY;

	//int sendto(int sockfd, const void *msg, int len, unsigned int flags, const struct sockaddr *to, socklen_t tolen);
	sendto(sockfd,(const char *) msg, len, 0,(const struct sockaddr *) &to, sizeof(to));

	if (sendto < 0) {
		perror("Could not connect to socket");
		exit(EXIT_FAILURE);
	}
}

void UDPclient::recMsgFr()
{

}

void UDPclient::closeSocket()
{
	//close(sockfd);
	close(sockfd);
	//shutdown(sockfd, 2);
}