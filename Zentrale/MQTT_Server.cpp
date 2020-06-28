#include "MQTT_Server.h"

MQTT_Server::MQTT_Server(){}
MQTT_Server::~MQTT_Server(){}

MQTT_Server::MQTT_Server(FileManagement* handle){

    this->fileHandle = handle;
    this->connect();
}

int MQTT_Server::connect(){

    mqtt::connect_options connectionOpts;
    std::string data;
    mqtt::const_message_ptr message;
    connectionOpts.set_keep_alive_interval(20);
    connectionOpts.set_clean_session(true);
    mqtt::async_client client(SRV_ADDR, CLIENT_ID);

    // Create the callback 
    callback cb(client, connectionOpts);
    client.set_callback(cb);
    client.set_message_callback([&](mqtt::const_message_ptr msg) {

        std::cout << "Received message: " << msg->get_payload_str() << std::endl;
        data = msg->get_payload_str();
    }); 

    std::cout << "Message: " << data << std::endl;

    // Connect
    try {
        
        std::cout << "Connecting..." << std::endl;
        client.connect(connectionOpts, nullptr, cb);
        client.start_consuming();

        while(std::tolower(std::cin.get()) != 'q'){

            message = client.consume_message();
            if(!message)
                break;

            std::cout << "MSG: " << message->get_payload_str();
        }
    }
    catch (const mqtt::exception&){

        std::cerr << "Error: Couldn't connect." << std::endl;
        return 1;
    }



    return disconnect(client);
}

int MQTT_Server::disconnect(mqtt::async_client& client){

    try {

        std::cout << "Disconnecting..." << std::flush;
        client.disconnect()->wait();
        std::cout << std::endl << "Done!" <<std::endl;
    }
    catch(const mqtt::exception & e){

        std::cerr << e.what() << std::endl;
        return 1;

    }
    return 0;
}


void MQTT_Server::writeMessage(){


}
