#include <iostream>
#include "mqtt/async_client.h"
#include "FileManagement.h"


class MQTT_Server {

    FileManagement* fileHandle;
    
    int disconnect(mqtt::async_client & client);
    void writeMessage();

public:
    int connect();
    MQTT_Server();
    MQTT_Server(FileManagement* handle);
    ~MQTT_Server();
};
