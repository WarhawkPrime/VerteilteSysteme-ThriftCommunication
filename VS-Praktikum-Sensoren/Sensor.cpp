
#include "Sensor.h"

Sensor::Sensor()
{
	udpc.close_socket();
}

Sensor::Sensor(double lowEnd, double highEnd, std::string type, int modus) : type {type}
{
	udpc.fill_serverInfo();
	udpc.create_socket();
	udpc.bind_socket();

	this->type = type;

	repeater(lowEnd, highEnd, modus);
}

void Sensor::repeater(double lowEnd, double highEnd, int modus)
{

	switch (modus)
	{
	default: return;
		break;
	case 1:					//Manuell
	{
		std::cout << "Manuell gestartet" << std::endl;
		int input = 0;
		while (input == 0)
		{
			std::cout << "0 drücken um Nachricht zu senden, eine andere Zahl um das Programm zu beenden" << std::endl;
			std::cin >> input;
			this->data = random_value(lowEnd, highEnd);
			this->now = getTime();
			udpc.send_msg_to(build_message());
		}
	};
		break;
	case 2:				//Automatik
		std::cout << "Automatik gestartet" << std::endl;
		while (true)
		{
			//std::cout << "test davor3" << std::endl;
			sleep_delay();
			//std::cout << "test danach3" << std::endl;

			this->data = random_value(lowEnd, highEnd);
			this->now = getTime();
			udpc.send_msg_to(build_message());
		};
		break;
	}
}

char* Sensor::build_message()
{
	char* message = "42";
	std::string s_msg;

	std::string port = udpc.get_port();
	port = port + ";";
	type = type + ";";

	s_msg = port + type;

	std::string data_s = std::to_string(get_data());
	data_s = data_s + ";";

	s_msg += data_s;

	std::string date_s = get_date();
	date_s += ";";

	s_msg += date_s;


	int s = udpc.get_buffer_size();
	char t[s];
	strcpy(t, s_msg.c_str());

	message = t;

	return message;
}

char* Sensor::getTime()
{
	time_t t = time(0);
	char* dt = ctime(&t);
	return dt;
}

double Sensor::random_value(double lowEnd, double highEnd)
{
	std::uniform_real_distribution<double> unif(lowEnd, highEnd);
	std::default_random_engine re;
	return unif(re);
}

void Sensor::sleep_delay()
{
	for (size_t i = 0; i < 10000000000; i++)
	{

	}
	//usleep(10000000);
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

/*


int input = 0;
		while (input = 0)
		{
			std::cout << "0 drücken um Nachricht zu senden, eine andere Zahl um das Programm zu beenden" << std::endl;
			std::cin >> input;
			this->data = random_value(lowEnd, highEnd);
			this->now = getTime();
			udpc.send_msg_to(build_message());
		};







while (true)
		{
			std::cout << "test davor3" << std::endl;
			//sleep_delay();
			std::cout << "test danach3" << std::endl;

			this->data = random_value(lowEnd, highEnd);
			this->now = getTime();
			udpc.send_msg_to(build_message());
		};

*/