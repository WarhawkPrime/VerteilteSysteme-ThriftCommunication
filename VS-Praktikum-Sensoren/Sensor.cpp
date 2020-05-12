
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
			std::cout << "0 druecken um Nachricht zu senden, eine andere Zahl um das Programm zu beenden" << std::endl;
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
			sleep_delay();

			this->data = random_value(lowEnd, highEnd);
			this->now = getTime();
			udpc.send_msg_to(build_message());
		};
		break;
	}
}

char* Sensor::build_message()
{
	char* message = "0";
	std::string s_msg = "0";

	//add port and type
	std::string port = udpc.get_port();
	port = port + ";";
	std::string type_s = get_type();
	type_s= type_s + ";";
	s_msg = port + type_s;

	//messwerte
	std::string data_s = std::to_string(get_data());
	data_s = data_s + ";";
	s_msg = s_msg + data_s;

	//datum
	std::string date_s = get_date();
	s_msg = s_msg + date_s;

	//umwandlung zum char*
	int s = udpc.get_buffer_size();
	char t[s];
	strcpy(t, s_msg.c_str());
	message = t;

	std::cout << s_msg << std::endl;

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

	for (size_t i = 0; i < 10000000000; i++)	//10.000.000.000
	{

	}

	/*
	std::cout << "Clock start" << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(std::chrono::seconds(10));

	usleep(10000000000);

	//std::thread t1(sleepThread);
	//t1.join();

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;
	std::cout << "Waited " << elapsed.count() << " ms\n";
	*/

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