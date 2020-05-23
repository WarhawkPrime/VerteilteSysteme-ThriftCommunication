#include "Client.h"

Client::Client() {
	tcp.fill_serverInfo();
	tcp.create_socket();
	tcp.connect_socket();
}

Client::~Client() {
	tcp.close_socket();
}

void const Client::start() {
	//loop to ask the server again
	for (;;) {
		this->dialog();			//creation of header and sending it
		//this->send_message();
		this->rec_message();
	}
}

/*Hier wird die Nachricht gebaut, erstmal nur aus dem Request-Header mit GET

GET		\r\n					get methode um daten anzufragen
HOST:		\r\n				host an den die Anfrage geht
CACHE:		\r\n				einstellungen ob/wie die Verbindung aufgezeichnet werden soll
DNT:		\r\n				einstellung ob der client gertracked werden darf
ACCEPT:		\r\n				welche art von datei aktzeptiert werden darf
ACCEPT-CHARSET:		\r\n		welcher charset aktzeptiert wird
CONNECTION:		\r\n			einstellung ob die connection offen gehalten werden soll oder geschlossen werden soll

Beispiel

GET http://serveradresse:80/c/username/dokuments/files/?param1=0\r\n
HOST: zentrale adresse\r\n
CACHE: max-age = 10\r\n
DNT: 1\r\n
ACCEPT: text/plain\r\n
ACCEPT-CHARSET: utf-8\r\n
CONNECTION: keep-alive\r\n
\r\n\r\n
*/

void Client::build_header(std::string path, std::string parameter) {

	std::string uri = "http://" + tcp.get_server_adress() + ":" + tcp.get_CPORT() + path + "?" + parameter;
	std::string message = "GET " + uri + "?" + parameter + "\r\n";
	message += "HOST: " + tcp.get_server_adress() + "\r\n";
	message += "CACHE: max-age = 10\r\n";
	message += "DNT: 1\r\n";
	message += "ACCEPT: text/plain\r\n";
	message += "ACCEPT_CHARSET: utf-8\r\n";
	message += "CONNECTION: keep-alive\r\n";
	message += "\r\n\r\n";

	char* msg = this->string_to_char(message);
	//char* msg = message.c_str();
	this->send_message(msg);

}

void const Client::send_message(char* msg) {

	tcp.send_msg_to(msg);
	std::cout << msg << " send" << std::endl;
}

/*
HTTP/1.1 200 ok\r\n
Content-type: text/html\r\n
Content-length: 41\r\n
\r\n\r\n
<html>hello world, account created</html>
*/

void Client::rec_message() {

	std::cout << tcp.rec_msg_fr() << std::endl;

	std::string received_request = tcp.rec_msg_fr();
	std::stringstream message_stream(received_request);
	std::string segment;
	
	int line = 0;
	while (std::getline(message_stream, segment, '\n')) {
		switch (line)
		{
		default:
			break;
		case 0: response.h1 = segment; 
			line++;
			break;
		case 1: response.content_type = segment; 
			line++;
			break;
		case 2: response.content_length = segment;
			line++;
			break;
		case 3: //leerstelle
			line++;
			break;
		case 4: response.message = segment;
			line++;
			break;
		}
	}
}

void const Client::dialog() {
	int input = 0;
	
	while (input >= 0) {
		std::cout << "select wanted ressource: " << std::endl;
		std::cout << "0 : current Sensor data" << std::endl;
		std::cout << "1 : all Sensor data" << std::endl;
		std::cout << "2 : all past Sensor data" << std::endl;
		std::cout << "-1  : end communication with server" << std::endl;

		std::cin >> input;

		switch (input)
		{
		default:  this->sensor_dialog();
			break;
		case 0:	this->sensor_dialog();
			break;
		case 1: this->build_header("hier könnte ihre URI stehen", "4");
			break;
		case 2: this->build_header("hier könnte ihre URI stehen", "5");
			break;
		}
	}
}

void const Client::sensor_dialog() {
	std::cout << std::endl;
	std::cout << "Sensor types" << std::endl;
	std::cout << "0 : all Temperature sensors" << std::endl;
	std::cout << "1 : all Wind sensors" << std::endl;
	std::cout << "2 : all Humidity sensors" << std::endl;
	std::cout << "3  : all Brightness sensors" << std::endl;

	int input = 0;
	std::cin >> input;

	switch (input) 
	{
	default: 
		break;
	case 0: std::cout << "all Temperature sensors" << std::endl;	this->build_header("hier könnte ihre URI stehen","0");
		break;
	case 1:	std::cout << "all Wind sensors" << std::endl;	this->build_header("hier könnte ihre URI stehen","1");
		break;
	case 2:	std::cout << "all Humidity sensors" << std::endl;	this->build_header("hier könnte ihre URI stehen","2");
		break;
	case 3:	std::cout << "all Brightness sensors" << std::endl;	this->build_header("hier könnte ihre URI stehen","3");
		break;
	}
}

char* Client::string_to_char(std::string string_to_c) {
	char char_arr[sizeof(string_to_c)];
	strcpy(char_arr, string_to_c.c_str());
	return char_arr;
}