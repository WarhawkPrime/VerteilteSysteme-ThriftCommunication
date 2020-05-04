
#include <iostream>
#include <unistd.h>

#include "SensorManagement.h"
#include "UDPclient.h"

//todo: UDP client schnittstelle, regelm‰ﬂige sendung der Daten bis der Sensor abgeschaltet wird

int main() {
	//SensorManagement sm;
	//sm.userDialog();

	int i;
	std::cout << "Bei eingabe von einer Zahl wird das Programm beendet" << std::endl;


	UDPclient udpc;

	udpc.fillServerInfo();
	udpc.createSocket();
	udpc.bindSocket();
	udpc.sendMsgTo();
	udpc.closeSocket();

	//nicht notwendig, h‰lt aber die Konsole l‰nger offen
	std::cout << "Bei eingabe von einer Zahl wird das Programm beendet" << std::endl;
	std::cin >> i;
}