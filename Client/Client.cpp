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
	while (true) {
		//loop to ask the server again
		this->dialog();			//creation of header and sending it
		//this->send_message();
		std::cout << "dialog ended" << std::endl;
		std::cout << std::endl;
		this->rec_message();
		this->interprete_message();
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

//htdocs
void Client::build_header(std::string path, std::string parameter) {

	std::string uri = "http://" + tcp.get_server_adress() + ":" + tcp.get_CPORT() + path;
	std::string message = "GET " + uri + "?" + parameter + "\r\n";
	message += "HOST: " + tcp.get_server_adress() + "\r\n";
	message += "CACHE: max-age = 10\r\n";
	message += "DNT: 1\r\n";
	message += "ACCEPT: text/plain\r\n";
	message += "ACCEPT_CHARSET: utf-8\r\n";
	message += "CONNECTION: keep-alive\r\n";
	message += "\r\n\r\n";

	const char* msg = message.c_str();

	std::cout << msg << std::endl;

	tcp.send_msg_to(msg);
}

/*
void const Client::send_message(char* msg) {

	tcp.send_msg_to(msg);
	std::cout << msg << " send" << std::endl;
}
*/

/*
HTTP/1.1 200 ok\r\n
Content-type: text/html\r\n
Content-length: 41\r\n
Connection: keep-alive\r\n
\r\n\r\n
<html>hello world, account created</html>
*/

void Client::rec_message() {

	std::string received_request;
	received_request = tcp.rec_msg_fr();
	std::stringstream message_stream;
	std::string s = message_stream.str();

	message_stream.str(std::string());
	message_stream.str(received_request);

	this->resp.message = "";

	//std::stringstream message_stream(received_request);
	std::string segment;

	int linecounter = 0;
	while (std::getline(message_stream, segment)) {
		std::cout << std::endl;
		switch (linecounter)
		{
		default:
			break;
		case 0: resp.h1 = segment.substr(9);
			linecounter++;
			break;
		case 1: resp.content_type = segment.substr(14);
			linecounter++;
			break;
		case 2: resp.content_length = segment.substr(16);
			linecounter++;
			break;
		case 3: resp.connection = segment.substr(12);
			linecounter++;
			break;
		case 4: // trennung von header zu message
			linecounter++;
			break;
		case 5:
			linecounter++;
			break;
		case 6: resp.message = segment;
			linecounter++;
			break;
		}
	}

	std::cout << std::endl;
	std::cout << "Erhaltende Nachricht: " << std::endl;
	std::cout << std::endl;
	std::stringstream message_stream2;
	message_stream2.str(std::string());
	message_stream2.str(received_request);

	while (std::getline(message_stream2, segment)) {
		std::cout << segment << std::endl;
	}
}


/*
tempFileName = "tempSensorData.txt";
lxDataFileName = "luxSensorData.txt";
allDataFileName = "allSensorData.txt";
hmdtyDataFileName = "hmdtySensorData.txt";
airSpdFileName = "airspdSensorData.txt";
*/
void const Client::dialog() {
	int input = 0;

	std::cout << "select wanted ressource: " << std::endl;
	std::cout << "0 :Temperature sensors" << std::endl;
	std::cout << "1 :Wind sensors" << std::endl;
	std::cout << "2 :Humidity sensors" << std::endl;
	std::cout << "3 :Brightness sensors" << std::endl;
	std::cout << "4 :All Sensor data" << std::endl;

	std::cin >> input;
	switch (input)
	{
	default:  std::cout << "auswahl nicht getroffen" << std::endl;
		this->dialog();
		break;
	case 0:	this->sensor_dialog("tempSensorData.txt");
		break;
	case 1:	this->sensor_dialog("airspdSensorData.txt");
		break;
	case 2: this->sensor_dialog("hmdtySensorData.txt");
		break;
	case 3: this->sensor_dialog("luxSensorData.txt");
		break;
	case 4: this->sensor_dialog("allSensorData.txt");
	}

	/*
		std::cout << "select wanted ressource: " << std::endl;
		std::cout << "0 : current Sensor data" << std::endl;	//aktueller Stand
		std::cout << "1 : all Sensor data" << std::endl;	//von jedem der neuste wert
		std::cout << "2 : all past Sensor data" << std::endl;	//vergangene Daten bis zu einer Grenze
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
	*/
}

void const Client::sensor_dialog(std::string uri) {
	std::cout << "bestimmte Auswahl treffen" << std::endl;

	std::cout << "0: current data" << std::endl;	//der letzte Wert des Sensortypes
	std::cout << "1: all Sensor data" << std::endl;	//alle vergangenen Daten des ausgewählten Sensort<pes
	std::cout << "2: past Sensor data" << std::endl;	//alle vergangenen Daten von allen Sensortypen

	int input = 0;
	std::cin >> input;
	if (input < 0 || input > 2) {
		input = 0;
	}

	std::string a = "=";
	std::string sPara = "param1";
	sPara += a + std::to_string(input);
	//+std::to_string(input);

	this->build_header(uri, sPara);


	/*
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
	*/
}

void Client::interprete_message() {
	std::string con = resp.connection;

	/*
	//expect more data
	if (con.find("keep") != std::string::npos) {
		std::cout << "keep-alive" << std::endl;
	}
	else {
		std::cout << "break connection" << std::endl;
		this->tcp.close_socket();
	}
	*/
}



/*
char* Client::string_to_char(std::string string_to_c) {
	char char_arr[sizeof(string_to_c)];
	strcpy(char_arr, string_to_c.c_str());
	return char_arr;
}
*/