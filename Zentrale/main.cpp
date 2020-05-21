#include <cstdio>
#include "Skynet.h"
#include <sys/select.h>
#include <thread>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <pthread.h>


void dosmth() {
    std::cout << "test" << std::endl;
};



int main()
{
    Skynet* skynet = new Skynet();

    std::thread t1(&Skynet::start_skynet_with_udp, skynet, "UDP-Server");
    std::thread t2(&Skynet::start_skynet_with_http, skynet, "HTTP-Server");

    t1.join();
    t2.join();

    return 0;
}
