#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include "mqtt/async_client.h"

// Define server address and name of client
const std::string SRV_ADDR("tcp://localhost:1883");
const std::string CLIENT_ID("zentrale");

//const std::string TMPSENSOR("Sensordata/temperatur");
//const std::string HMDSENSOR("Sensordata/humidity");
//const std::string ARSSENSOR("Sensordata/windspeed");
//const std::string LUXSENSOR("Sensordata/brightness");





// Define callback functions for success or failure of operations
class action_listener : public virtual mqtt::iaction_listener
{
    std::string name;
    
    void on_failure(const mqtt::token &token) override {
        
        std::cout << name << " failure";
        if(token.get_message_id() != 0)
            std::cout << "for token: [" << token.get_message_id() << "]" << std::endl;
        std::cout << std::endl;
    }

    void on_success(const mqtt::token &token) override {
        
        std::cout << name << " success";
		if (token.get_message_id() != 0)
			std::cout << " for token: [" << token.get_message_id() << "]" << std::endl;
		
        auto top = token.get_topics();
		if (top && !top->empty())
			std::cout << "\ttoken topic: '" << (*top)[0] << "'" << std::endl;
		std::cout << std::endl;
    }

    public:
    action_listener(const std::string &name) : name(name) {}


};

// Define callback functions for client connection, receives messages and handles the connection
class callback : public virtual mqtt::callback, public virtual mqtt::iaction_listener
{
    int retries;
    mqtt::async_client & client;
    mqtt::connect_options& connectionOpts;
    action_listener listener;
    // Define quality of service and max num of retry attempts on failed connection
    const int QOS = 1;
    const int NUM_RTRYS = 2;
    std::string TOPIC[4] = {
    "Sensordata/temperatur",
    "Sensordata/humidity",
    "Sensordata/windspeed",
    "Sensordata/brightness"
    };



    // Mannually reconnect to the broker by calling connect again.
    void reconnect() {
        
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
        try{

            client.connect(connectionOpts, nullptr, *this);
        }
        catch (const mqtt::exception & e){

            std::cerr << "Error: " << e.what() << std::endl;
            exit(1);
        }
    }

    // Reconnection failed
    void on_failure(const mqtt::token & token) override {

        std::cout << "Failed to connect!" << std::endl;
        if(++retries > NUM_RTRYS)
            exit(1);
        reconnect();
    }

    // (Re)connection success
    void on_success(const mqtt::token & token) override {}

    // (Re)connection success
    void connected(const std::string & cause) override {

        std::cout << "Established Connection" << std::endl;
        for(int i = 0; i < 4; i++){
            
            std::cout << "Subscribing to topic: '" << TOPIC[i] << "'" << std::endl;
            client.subscribe(TOPIC[i], QOS, nullptr, listener);
        }
        
    }

    // On connection loss, try to reconnect
    void connection_lost(const std::string & cause) override {

        std::cout << "Lost connection" << std::endl;
        std::cout << "Trying to reconnect..." << std::endl;
        retries = 0;
        reconnect();
    }

    // Callback for arriving message
    void message_arrived(mqtt::const_message_ptr msg) override {}
    void delivery_complete(mqtt::delivery_token_ptr token) override {}


public:
    callback(mqtt::async_client& cli, mqtt::connect_options& connOpts)
				: retries(0), client(cli), connectionOpts(connOpts), listener("Subscription") {}

};
