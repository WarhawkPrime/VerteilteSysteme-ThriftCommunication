#include "Client.h"

Client::Client() {
	tcp.fill_serverInfo();
	tcp.create_socket();
	tcp.connect_socket();
}

Client::~Client() {
	tcp.close_socket();
}

void Client::start() {
	this->dialog();			//creation of header
	this->sendMessage();
	this->recMessage();
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
void Client::buildHeader(std::string uri) {

}

void Client::sendMessage() {

	char* msg = "Hallo";

	tcp.send_msg_to(msg);

	std::cout << msg << "send" << std::endl;
}

void Client::recMessage() {

	tcp.rec_msg_fr();

}

void Client::dialog() {
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
		default:  
			break;
		case 0:	this->sensorDialog();
			break;
		case 1: this->buildHeader("hier könnte ihre URI stehen");	this->buildHeader("1");
			break;
		case 2: this->buildHeader("hier könnte ihre URI stehen");	this->buildHeader("2");
			break;
		case -1:
			break;
		}
	}
}

void Client::sensorDialog() {
	std::cout << std::endl;
	std::cout << "Sensor types" << std::endl;

	int input = 0;

	switch (input) 
	{
	default: 
		break;
	case 0: std::cout << "all Temperature sensors" << std::endl;	this->buildHeader("3");
		break;
	case 1:	std::cout << "all Wind sensors" << std::endl;	this->buildHeader("4");
		break;
	case 2:	std::cout << "all Humidity sensors" << std::endl;	this->buildHeader("5");
		break;
	case 3:	std::cout << "all Brightness sensors" << std::endl;	this->buildHeader("6");
		break;
	}
}