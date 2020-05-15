#include <cstdio>
#include "UDP_server.h"

int main()
{
    //Start Server
    UDP_server* srv = new UDP_server();
    srv->initialize();
    return 0;
}