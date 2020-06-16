#include <cstdio>
#include "unistd.h"

#include <iostream>
#include <unistd.h>

#include "Sensor_Management.h"
#include "UDP_Socket.h"

#include <thread>
#include <chrono>

#include "Sensor_Management.h"

/*
	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;
	std::cout << "Waited " << elapsed.count() << " ms\n";
	*/

int main(int argc, char* argv[]) {
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
