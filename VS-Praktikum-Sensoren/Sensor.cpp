
#include "Sensor.h"

Sensor::Sensor()
{
	udpc.closeSocket();
}

Sensor::Sensor(double lowEnd, double highEnd, std::string type) : type {type}
{
	udpc.fillServerInfo();
	udpc.createSocket();
	udpc.bindSocket();

	repeater(lowEnd, highEnd);
}

char* Sensor::getTime()
{
	time_t t = time(0);
	char* dt = ctime(&t);
	return dt;
}

double Sensor::randomValue(double lowEnd, double highEnd)
{
	std::uniform_real_distribution<double> unif(lowEnd, highEnd);
	std::default_random_engine re;
	return unif(re);
}

void Sensor::repeater(double lowEnd, double highEnd)
{

		this->type = type;
		this->data = randomValue(lowEnd, highEnd);
		this->now = getTime();

		udpc.sendMsgTo(buildMessage());

}

char* Sensor::buildMessage()
{
	return "Dies ist eine Testnachricht";
}


/*
UDPclient udpc;

	udpc.fillServerInfo();
	udpc.createSocket();
	udpc.bindSocket();
	std::cout << "vor msg" << std::endl;
	udpc.sendMsgTo();
	std::cout << "nach msg" << std::endl;
	udpc.closeSocket();
*/