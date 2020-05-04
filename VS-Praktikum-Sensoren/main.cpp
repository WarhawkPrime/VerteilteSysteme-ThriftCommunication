
#include <iostream>
#include <unistd.h>

#include "SensorManagement.h"
#include "UDPclient.h"

//todo: UDP client schnittstelle, regelm‰ﬂige sendung der Daten bis der Sensor abgeschaltet wird

int main() {
	SensorManagement sm;
	sm.userDialog();
}