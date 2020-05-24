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
#define CPORT	"50000"
#define IPORT	50000

class UDP_Socket
{
	struct sockaddr_in servaddr;
	struct sockaddr_in to;

	struct addrinfo hints;
	struct addrinfo* res, * rp;

public:
	UDP_Socket();
	~UDP_Socket();

	void fill_serverInfo();
	void create_socket();		//create the socket
	void bind_socket();			//bind the socket to an address-unnecessary for a client
	void connect_socket();		//connect to a server
	void send_msg_to(char* msg);			//send repeatingly until we have or receive data
	void rec_msg_fr();
	void close_socket();			//close to release the data

	//========== Getter & Setter ==========
	int get_sockfd() const { return sockfd; }
	char* get_buffer() { return buffer; }
	ssize_t get_leng() { return len; }
	socklen_t get_addr_size() { return addrSize; }

	char* get_port() const { return CPORT; }
	int get_buffer_size() const { return BUF_SIZE; }

private:
	int sockfd;				//file description
	char buffer[BUF_SIZE];		//buffer für die Übertragung
	int send;
	int recv;
	size_t len;
	ssize_t nread;
	socklen_t addrSize;
};

