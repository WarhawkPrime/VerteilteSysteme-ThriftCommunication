#pragma once

#include <ctime>

class Timer
{
public:
	Timer() {}
	~Timer() {}

	void start() {
		start_time = clock();
	}

	unsigned long elapse_time() {
		return ((unsigned long)clock() - start_time) / CLOCKS_PER_SEC;
	}

	bool is_timeout(unsigned long seconds) {
		return seconds >= elapse_time();
	}

private:
	unsigned long start_time;
};

