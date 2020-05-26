#pragma once

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


#define BUF_SIZE 2000
#define CPORT	"80"
#define IPORT	80

/*
socket()

connect()

send()

recv()

*/

class TCP_Socket
{
public:

	TCP_Socket();
	~TCP_Socket();

	struct sockaddr_in servaddr;
	struct sockaddr_in to;

	struct addrinfo hints;
	struct addrinfo* res, * rp;

	void fill_serverInfo();
	void create_socket();		//create the socket
	//void bind_socket();			//bind the socket to an address-unnecessary for a client
	void connect_socket();		//connect to a server
	void send_msg_to(const char* msg);			//send repeatingly until we have or receive data
	std::string rec_msg_fr();
	void close_socket();			//close to release the data

	//========== Getter & Setter ==========
	std::string get_CPORT() const { return CPORT; }
	int get_sockfd() const { return sockfd; }
	char* get_buffer() { return buffer; }
	ssize_t get_leng() const { return len; }
	socklen_t get_addr_size() const { return addrSize; }
	char* get_port() const { return CPORT; }
	int get_buffer_size() const { return BUF_SIZE; }
	std::string get_server_adress() const { return std::to_string(servaddr.sin_addr.s_addr); }

private:
	int sockfd;				//file description
	char buffer[BUF_SIZE];		//buffer f�r die �bertragung
	size_t len;
	ssize_t nread;
	socklen_t addrSize;
};

