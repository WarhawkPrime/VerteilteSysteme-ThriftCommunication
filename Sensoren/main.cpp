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

int main() {

	Sensor_Management sm;
	sm.user_dialog();

	return 0;
}