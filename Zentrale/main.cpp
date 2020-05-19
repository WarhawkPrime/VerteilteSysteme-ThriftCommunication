#include <cstdio>
#include "Skynet.h"
#include <sys/select.h>
#include <thread>


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
//TO DO => start the different functions in a thread to ensure that all requests can get through


void dosmth() {
    std::cout << "test" << std::endl;
};


int main()
{
    
    Skynet skynet;
    
    std::thread t1(dosmth);
    t1.detach();
    return 0;
    
}
