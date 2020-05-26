#pragma once

//TCP-Socket PORT 80 !!!!

//TO DO => implementierung von einfachem http-server der den GET Befehl korrekt verarbeiten kann
//TO DO => http schnittstelle über eine REST-API den Zugriff auf die Sensordaten mit historie (mit jeweils eigener URI) (Unifiorm Resource Identifier)
//REST API -> Representational State Transfer, Application Programming Interface

/*
When you don't want to use an external library, you will have to implement HTTP yourself. When you only need the basic functionality (direct download of a file, no redirects, no proxies, no cookies, no authentication, no encryption, no compression, no other shenanigans), this isn't even that hard.

Create a socket, connect it to port 80 of your webserver, and send the following strings to the server:

"GET /example.html HTTP/1.1\r\n"
"Host: www.example.com\r\n"
"\r\n"
This requests the file www.example.com/example.html from the server you connected to.

The server will respond with an own HTTP response header followed by the data (or an error description).
*/


/*

SERVER				CLIENT




socket()			socket()
					
bind()				
					
listen()	.	.	connect()
			.
accept()  < .		


				. .	send()
recv()	<. .  .	. 


send()	.	.
			.	. >	recv()


*/


//http wird genutzt in Verbindung mit TCP
//jede Zeile im Header als Paar key : value
//ende mit leerzeile (\r\n\r\n)
//beispiel http


//client->server(request)

//GET /test?param1=1&param2=2 HTTP/1.1\r\n
//HOST: 123:234.123.234:80\r\n
//User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.10; rv:41.0)\r\n
//Gecko/20100101 Firefox/41.0\r\n
//Accept:\r\n
//text/html,application/xhtml+xml,application/xml;q=0.9.*/*;q=0.8\r\n
//Accept-Language: de,en-US;q=0.7,en;q=0.3\r\n
//Accept-Encoding: gzip, deflate\
//DNT: 1\r\n
//Connection : keep - alive\r\n
//Cache - Control : max - age = 0\r\n
//\r\n\r\n

//server->client(response)

//HTTP/1.1 200 ok\r\n
//Content-type: text/html\r\n
//Content-length: 41\r\n
//\r\n\r\n
//<html>hello world, account created</html>

//client->server(request)

//GET / test ? param1 = 1 & param2 = 2 HTTP / 1.1\r\n
//Host : 123 : 234.123.234 : 80\r\n
//User - Agent : Mozilla / 5.0 (Macintosh; Intel Mac OS X 10.10; rv:41.0)\r\n
//Gecko / 20100101 Firefox / 41.0\r\n
//Accept :\r\n
//text / html, application / xhtml + xml, application / xml; q = 0.9, */*;q=0.8\r\n
//Accept-Language: de,en-US;q=0.7,en;q=0.3\r\n
//Accept-Encoding: gzip, deflate\r\n
//DNT: 1\r\n
//Connection: keep-alive\r\n
//Cache-Control: max-age=0\r\n
//\r\n\r\n


//==================== VORGEHEN ===============

/*
TCP Socket und Client erstellen, dann einfach mit Strings oder ähnlichem die HTTP Anfragen etc schicken

*/

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netdb.h>
#include <vector>
#include <algorithm>
#include "Telemetry_data.h"

#define MAX_BUFFER 1024

// Request struct to store information about a request
struct request {

	std::string req;
	std::string host;
	std::string cache;
	std::string dnt;
	std::string accept;
	std::string accept_charset;
	std::string connection;
};

enum REQUEST{
	REQ,
	HOST,
	CACHE,
	DNT,
	ACCEPT,
	ACCEPT_CHARSET,
	CONNECTION
};

class HTTP_Server
{
private:

	// Variables
	bool BAD_REQUEST;
	int sockfd, child_sockfd, port, pid;
	struct sockaddr_in client_addr, server_addr;
	struct addrinfo hints;
	socklen_t client_addr_length;
	char readBuffer[MAX_BUFFER];
	std::vector<std::string>* currentSensorInfo;
	Telemetry_data* fileHandle;
	int handleConnection(int newSockfd); // Handles each connection and processes requests
	int sendResponse(int sockfd, std::string resp);
	int handleRequest(int sockfd, std::string req);
	std::string* fetchRequestedData(std::vector<std::string>* requestParameters, request &r);
	std::string createResponse(std::string* requestedData, request &requestParameters);
public:
	HTTP_Server(Telemetry_data* fh);
	~HTTP_Server();
	int createConnection(); // Generates socket and child processes, listens for incoming connections
	


};

