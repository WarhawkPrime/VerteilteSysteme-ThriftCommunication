#include "ActionListener.h"
#include "MQTT_Server.h"

MQTT_Server::MQTT_Server(){}
MQTT_Server::~MQTT_Server(){}

MQTT_Server::MQTT_Server(FileManagement* handle){

    this->fileHandle = handle;
    this->connect();
}

int MQTT_Server::connect(){

    mqtt::connect_options connectionOpts;
    std::string data, topic;
    mqtt::const_message_ptr message;
    connectionOpts.set_keep_alive_interval(0);
    connectionOpts.set_clean_session(true);
    mqtt::async_client client(SRV_ADDR, CLIENT_ID);

    // Create the callback 
    callback cb(client, connectionOpts);
    client.set_callback(cb);
    client.set_message_callback([&](mqtt::const_message_ptr msg) {
        std::cout << ">-MQTT------------------------------------------------------------------------<" << std::endl;
        std::cout << "Received message: " << msg->get_payload_str() << std::endl;
        std::cout << ">------------------------------------------------------------------------<" << std::endl;
        data = msg->get_payload_str();
        topic = msg->get_topic();
    }); 


    // Connect
    try {
        std::cout << ">-MQTT------------------------------------------------------------------------<" << std::endl;
        std::cout << "Connecting..." << std::endl;
        std::cout << ">------------------------------------------------------------------------<" << std::endl;
        client.connect(connectionOpts, nullptr, cb);
        client.start_consuming();

        // std::tolower(std::cin.get()) != 'q'
        while(1){

           message = client.consume_message();

           if(topic == "Sensordata/temperatur"){
               
               fileHandle->writeMQTTToFile(data, fileHandle->getTemp(), "1883");
           }
           else if(topic == "Sensordata/brightness"){
            
               fileHandle->writeMQTTToFile(data, fileHandle->getLux(), "1883");
           }
           else if(topic == "Sensordata/windspeed"){

                fileHandle->writeMQTTToFile(data, fileHandle->getAirspd(), "1883");
           }
           else if(topic == "Sensordata/humidity"){
            
               fileHandle->writeMQTTToFile(data, fileHandle->getHumidty(), "1883");
           }
           else{
               std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
               std::cout << "Topic error!" << std::endl;
               std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
               return 1;
           }
            
        }
        client.stop_consuming();
    }
    catch (const mqtt::exception&){
        std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
        std::cerr << "Error: Couldn't connect." << std::endl;
        std::cout << ">xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<" << std::endl;
        return 1;
    }



    return disconnect(client);
}

int MQTT_Server::disconnect(mqtt::async_client& client){

    try {
        std::cout << ">-MQTT------------------------------------------------------------------------<" << std::endl;
        std::cout << "Disconnecting..." << std::flush;
        client.disconnect()->wait();
        std::cout << std::endl << "Done!" <<std::endl;
        std::cout << ">------------------------------------------------------------------------<" << std::endl;
    }
    catch(const mqtt::exception & e){

        std::cerr << e.what() << std::endl;
        return 1;

    }
    return 0;
}


void MQTT_Server::writeMessage(){


}
