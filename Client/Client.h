#pragma once

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


class Client
{
public:


private:
	TCP_Socket tcp;
};

