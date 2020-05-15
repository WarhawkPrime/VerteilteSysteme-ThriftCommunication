#pragma once

#include "UDP_server.h"
#include "HTTP_Server.h"

class Skynet
{
public:
	Skynet() {}
	~Skynet(){}

	void start_skynet();

private:
	UDP_server udp;
	HTTP_Server http;
};