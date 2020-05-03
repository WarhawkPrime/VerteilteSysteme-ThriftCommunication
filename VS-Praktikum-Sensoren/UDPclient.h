#pragma once
//aufbau:
/*
socket()

bind()

sendto()

recvfrom()

closesocket()

*/

#include <iostream>

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define CPORT	"40000"
#define IPORT	40000


class UDPclient
{
	//struct sockaddr_in servaddr;
	//struct sockaddr_in cliaddr;

	struct addrinfo info;
	struct addrinfo *res;
	struct sockaddr_in to;

public:
	UDPclient();
	~UDPclient();

	void fillServerInfo();
	void createSocket();
	void bindSocket();
	void connectSocket();
	void sendMsgTo();
	void recMsgFr();
	void closeSocket();

	//getter
	int getSockfd() const { return sockfd;  }
	char* getBuffer() { return buffer; }

	char* getMessage() { return message; }	//späterer Austausch davon?

private:
	int sockfd;				//file description
	char buffer[1028];		//buffer für die Übertragung
	char* message;			//Nachricht als char*, hier evtl austauschen zur CSV datei
	int send;
	int recv;
	unsigned int lenght;
};

