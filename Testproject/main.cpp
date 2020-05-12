
#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "../VS-Praktikum-Zentrale/udp_server.h"
#include "../VS-Praktikum-Sensoren/SensorManagement.h"

TEST_CASE("test the test method") {
	CHECK(1 == 1);
}

TEST_CASE("2 test") {
	CHECK(1 == 1);
}

int main(int argc, char** argv) {
	
	doctest::Context context;

	context.setOption("order by", "name");
	context.applyCommandLine(argc, argv);

	int res = context.run();

	if (context.shouldExit()) {
		return res;
	}
	
	return res;
}