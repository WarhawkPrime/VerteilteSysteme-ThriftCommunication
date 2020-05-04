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

#define BUF_SIZE 500
#define CPORT	"40000"
#define IPORT	40000


class UDPclient
{
	struct sockaddr_in servaddr;
	//struct sockaddr_in cliaddr;

	struct sockaddr_in to;

	struct addrinfo hints;
	struct addrinfo *res, *rp;

public:
	UDPclient();
	~UDPclient();

	void fillServerInfo();
	void createSocket();		//create the socket
	void bindSocket();			//bind the socket to an address-unnecessary for a client
	void connectSocket();		//connect to a server
	void sendMsgTo();			//send repeatingly until we have or receive data
	void recMsgFr();
	void closeSocket();			//close to release the data

	//getter
	int getSockfd() const { return sockfd;  }
	char* getBuffer() { return buffer; }
	ssize_t getLen() { return len; }
	socklen_t getAddrSize() { return addrSize; }

	char* getMessage() { return message; }	//späterer Austausch davon?

private:
	int sockfd;				//file description
	char buffer[BUF_SIZE];		//buffer für die Übertragung
	char* message;			//Nachricht als char*, hier evtl austauschen zur CSV datei
	int send;
	int recv;
	size_t len;
	ssize_t nread;
	socklen_t addrSize;
};

