
#include "Sensor.h"

Sensor::Sensor()
{

}

Sensor::Sensor(double lowEnd, double highEnd, std::string type) : type {type}
{
	this->type = type;
	this->data = randomValue(lowEnd, highEnd);
	this->now = getTime();
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
