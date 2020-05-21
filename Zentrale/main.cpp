#include <cstdio>
#include "Skynet.h"
#include <sys/select.h>
#include <thread>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


void dosmth(Skynet* skynet) {
    std::cout << "test_u" << std::endl;

    skynet->start_skynet_with_udp();

    std::cout << "test_ue" << std::endl;
};

void dosmth2(Skynet* skynet) {
    std::cout << "test_h" << std::endl;

    skynet->start_skynet_with_http();

    std::cout << "test_he" << std::endl;
};



int main()
{
    Skynet* skynet = new Skynet();

    std::thread t1(dosmth, skynet);
    std::thread t2(dosmth2, skynet);
    t1.join();
    t2.join();

    /*
    std::thread t1(&Skynet::start_skynet_with_udp, skynet, "UDP-Server");
    std::thread t2(&Skynet::start_skynet_with_http, skynet, "HTTP-Server");

    t1.join();
    t2.join();
    */
    return 0;
}
