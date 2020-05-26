#pragma once

#include <string>
#include <sstream>

#include "TCP_Socket.h"

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


//client braucht die Möglichkeit, einzelne Sensordaten, alle Sensordaten oder die Historie der Sensordaten zu bekommen.
//jeder einzelne Bereich hat eine eigene URI -> Uniform Resource Identifier
// -> string of characters that unambiguously identifies a particular resource
//
//			URI = scheme:[//authority]path[?query][#fragment]
//			authorory = [userinfo@]host[:port]

//example:	https://john.do@www.example.com:123/forum/question/?tag=networking&order=newest#top

//	scheme : http, https, mailto, file, data, irc
//	authority : optional : userinfo and optional passwort (username:passwort) | host(name or ip address) | port
//	path : always defined for an URI | can map exactly to a file system path
//	optional query sequence of attribute-value pairs ( key1=value&key2=value2 )
//	optional fragment, secondary resource


//	accept : type/subtype [q=qvalue] zb Accept: text/plain
//										Accept-Charset: utf-8

//=============================================================================================================================================

/*
Vorgehen:

Socket aufbauen
Nachricht aufbauen mit GET Method
Auf Nachricht des Servers warten
Nachricht Zeile für Zeile auslesen und die Werte dann zuordnen

*/

/*
GET http ://serveradresse:80/c/username/dokuments/files/?param1=0\r\n
HOST: zentrale adresse\r\n
CACHE : max - age = 10\r\n
DNT : 1\r\n
ACCEPT : text / plain\r\n
ACCEPT - CHARSET: utf - 8\r\n
CONNECTION : keep - alive\r\n
\r\n\r\n
*/
struct request {

};

/*
HTTP/1.1 200 ok\r\n
Content-type: text/html\r\n
Content-length: 41\r\n
\r\n\r\n
<html>hello world, account created</html>
*/

/*
HTTP/1.1 200 OK
Date: Fri, 06 Nov 2009 00:35:42 GMT
Server: Apache
Content-Length: 0
Keep-Alive: timeout=15, max=100
Connection: Keep-Alive
Content-Type: text/plain
*/

struct response {
	std::string h1;
	std::string content_type;
	std::string content_length;
	std::string message;
};

class Client
{
public:

	Client();
	~Client();

	void const dialog();
	void const sensor_dialog(std::string uri);

	void build_header(const std::string uri,const std::string parameter);
	//void const send_message(char* msg);
	void rec_message();

	//char* string_to_char(std::string string);

	void const start();

private:
	TCP_Socket tcp;
	response resp;
};

