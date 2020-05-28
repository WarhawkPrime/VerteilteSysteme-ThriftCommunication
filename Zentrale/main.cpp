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

    skynet->start_skynet_with_udp();
};

void dosmth2(Skynet* skynet) {
 
    skynet->start_skynet_with_http();
};

int main()
{
    Skynet* skynet = new Skynet();

    pid_t pid = fork();

    if (pid == 0)
    {
        // child process
        skynet->start_skynet_with_http();
    }
    else if (pid > 0)
    {
        // parent process
        skynet->start_skynet_with_udp();
    }
    else
    {
        // fork failed
        printf("fork() failed!\n");
        return 1;
    }

    //skynet->start_skynet_with_udp();
    //std::thread t1(dosmth, skynet);
    //std::thread t2(dosmth2, skynet);
    //t1.join();
    //t2.join();

    /*
    std::thread t1(&Skynet::start_skynet_with_udp, skynet, "UDP-Server");
    std::thread t2(&Skynet::start_skynet_with_http, skynet, "HTTP-Server");

    t1.join();
    t2.join();
    */
    return 0;
}
