
#include <iostream>
#include <unistd.h>

#include "SensorManagement.h"
#include "UDPclient.h"
#include "Timer.h"

#include <thread>
#include <chrono>

/*
	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;
	std::cout << "Waited " << elapsed.count() << " ms\n";
	*/

int main() {

	SensorManagement sm;
	sm.user_dialog();

	return 0;
}