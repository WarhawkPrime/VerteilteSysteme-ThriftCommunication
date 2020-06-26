#include <cstdio>
#include "unistd.h"

#include <iostream>
#include <unistd.h>

#include "Sensor_Management.h"
#include "UDP_Socket.h"

#include <thread>
#include <chrono>

#include "Sensor_Management.h"

#include "mqtt/async_client.h"

const std::string DFLT_ADDRESS {"tcp://localhost:1883"};
const std::string TOPIC {"data/rand"};
const int QOS = 1;
const int MAX_BUFFERED_MSGS = 120;
const std::string PERSIST_DIR {"data-persist"};

/*
	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;
	std::cout << "Waited " << elapsed.count() << " ms\n";
	*/

int main(int argc, char* argv[]) {


	std::string address = "localhost";
	mqtt::async_client cli(address, "", MAX_BUFFERED_MSGS, PERSIST_DIR);

	std::string stringID = "0";
	if (argv[1] != NULL) {
		stringID = argv[1];
	}
	else {
		std::cout << "kein Argument übergeben" << std::endl;
		std::cout << "Argument: " << std::endl;
		std::cin >> stringID;
	}

	Sensor_Management sm;
	sm.user_dialog(stringID);

	return 0;
}
