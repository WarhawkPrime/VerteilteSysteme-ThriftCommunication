
#include "MQTT_Sensor.h"


MQTT_Sensor::MQTT_Sensor(double lowEnd, double highEnd, std::string type, int modus, std::string client_id) : 
				type(type), client_id(client_id)
 {
	this->repeater(lowEnd, highEnd, modus, type);
}


void MQTT_Sensor::repeater(double lowEnd, double highEnd, int modus, std::string type)
{

	
	const char* LWT_PAYLOAD = "Last will and Testament.";	
	
	std::string topic = "default";
	

	if(type == "temperatursensor") {
        	topic = "Sensordata/temperatur";
        }
        else if(type == "helligkeitssensor") {
                topic = "Sensordata/brightness";
        }
        else if(type == "windsensor") {
                topic = "Sensordata/windspeed";
        }
        else if(type == "luftfeuchtigkeitssensor") {
                topic = "Sensordata/humidity";
        }
        else {
                        std::cerr << "wrong type" << std::endl;
        }

	//const std::string TOPIC = { "Sensordata/temperatur" };
	//const std::string TOPIC = { "Sensordata/brightness" };
	//const std::string TOPIC = { "Sensordata/windspeed" };
	//const std::string TOPIC = { "Sensordata/humidity" };

	
	const std::string TOPIC = { topic };
	std::string address = DFLT_SERVER_ADDRESS;
	std::string client_id = get_client_id();

	std::cout << "Initializing for server '" << address << "'..." << std::endl;
	mqtt::async_client client(address, client_id);

	callback cb;
	client.set_callback(cb);

	mqtt::connect_options conopts;
	mqtt::message willmsg(TOPIC, LWT_PAYLOAD, 1, true);
	mqtt::will_options will(willmsg);
	conopts.set_will(will);

	std::cout << "  ...OK" << std::endl;
	
	try {
		std::cout << "\nConnecting..." << std::endl;
		mqtt::token_ptr conntok = client.connect(conopts);
		std::cout << "Waiting for the connection..." << std::endl;
		conntok->wait();
		std::cout << "  ...OK" << std::endl;

		switch (modus)
		{
			default: return;
				break;
			case 0:
			{
			};
			break;
			case 1:					//Manuell
			{
				std::cout << "Manuell gestartet" << std::endl;

				int input = 0;
				
				while (input == 0)
				{

					this->data = random_value(lowEnd, highEnd);
								this->now = getTime();

					std::string message = build_message();			

					const char* PAYLOAD2 = message.c_str();

					std::cout << "0 druecken um Nachricht zu senden, eine andere Zahl um das Programm zu beenden" << std::endl;
					std::cin >> input;
					
					//const char* PAYLOAD2 = build_message();
					const int QOS = 1;
					const auto TIMEOUT = std::chrono::seconds(10);
					// Now try with itemized publish.
					

					std::cout << "\nSending next message..." << std::endl;
					mqtt::delivery_token_ptr pubtok;
					pubtok = client.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2), QOS, false);
					std::cout << "  ...with token: " << pubtok->get_message_id() << std::endl;
					std::cout << "  ...for message with " << pubtok->get_message()->get_payload().size()
						<< " bytes" << std::endl;
					pubtok->wait_for(TIMEOUT);
					std::cout << "  ...OK" << std::endl;

					
				}
			};
			break;
			case 2:				//Automatik
			{
				std::cout << "Automatik gestartet" << std::endl;
				
				
				while (true)
				{
					//	sleep_delay();

		
					std::this_thread::sleep_for(std::chrono::seconds(60));

					this->data = random_value(lowEnd, highEnd);
								this->now = getTime();

								const char* PAYLOAD2 = build_message();
								const int QOS = 1;
								const auto TIMEOUT = std::chrono::seconds(10);
								// Now try with itemized publish.

								std::cout << "\nSending next message..." << std::endl;
								mqtt::delivery_token_ptr pubtok;
								pubtok = client.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2), QOS, false);
								std::cout << "  ...with token: " << pubtok->get_message_id() << std::endl;
								std::cout << "  ...for message with " << pubtok->get_message()->get_payload().size()
										<< " bytes" << std::endl;
								pubtok->wait_for(TIMEOUT);
								std::cout << "  ...OK" << std::endl;

			
				};
			};	
			break;		
		};
		
		auto toks = client.get_pending_delivery_tokens();
		if (!toks.empty())
			std::cout << "Error: There are pending delivery tokens!" << std::endl;

		// Disconnect
		std::cout << "\nDisconnecting..." << std::endl;
		conntok = client.disconnect();
		conntok->wait();
		std::cout << "  ...OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}
		
}





double MQTT_Sensor::random_value(double lowEnd, double highEnd) {
	
	//std::uniform_real_distribution<double> unif(lowEnd, highEnd);
	std::random_device rd;
	unsigned seed = rd();
	std::default_random_engine re(seed);
	std::uniform_real_distribution<double> unif(lowEnd, highEnd);
	//return unif(re);
	return unif(re);
}

char* MQTT_Sensor::getTime()
{
	time_t t = time(0);
	char* dt = ctime(&t);
	return dt;
}

std::string MQTT_Sensor::build_message()
{
	
	//char* message = "0";
	std::string s_msg = "";

	//start with id
	std::string id = this->get_client_id();
	id = id + ";";

	//add port and type
	std::string port = "1883";
	port = port + ";";

	//sensor type
	std::string type_s = get_type();
	type_s = type_s + ";";
	s_msg = id + port + type_s;

	//messwerte
	std::string data_s = std::to_string(this->get_data());
	data_s = data_s + ";";
	s_msg = s_msg + data_s;

	//datum
	std::string date_s = get_date();
	s_msg = s_msg + date_s;

	
	return s_msg;
}
