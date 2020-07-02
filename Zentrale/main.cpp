#include "Skynet.h"
#include <sys/select.h>
#include <thread>
#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{


    int status = 0;
    pid_t pid, wpid;

    std::cout << "Test" << std::endl;

    //Father code
    Skynet* skynet = new Skynet();


    int n = 3;
    for (int id = 0; id < n; id++) {
        if ((pid = fork() == 0)) {

            if (id == 0) {
                pid = getpid();
                std::cout << ">-HTTP------------------------------------------------------------------------<" << std::endl;
                std::cout << "first child pid: " << pid << std::endl;
               
                skynet->start_skynet_with_http();
                exit(0);
            }
            else if (id == 1) {
                pid = getpid();
                std::cout << ">-MQTT------------------------------------------------------------------------<" << std::endl;
                std::cout << "second child pid: " << pid << std::endl;
                
                skynet->start_skynet_with_mqtt();
                exit(0);
            }
            else if (id == 2) {
                pid = getpid();
                std::cout << ">-THRIFT------------------------------------------------------------------------<" << std::endl;
                std::cout << "third child pid: " << pid << std::endl;
                
                skynet->start_skynet_with_thrift();
                exit(0);
            }
            else {
                std::cerr << "error" << std::endl;
            }
        }
    }
    while ((wpid = wait(&status)) > 0);
    std::cout << "father ends" << std::endl;
    

    return 0;

}
