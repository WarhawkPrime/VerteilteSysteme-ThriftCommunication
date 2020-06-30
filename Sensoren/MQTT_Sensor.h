#pragma once 

/*
Create a client object
set the options to connect to an MQTT server
set up callback functions
connect the client to an MQTT server
subscribe to any topics the client needs to receive
Repeat until finished:
	Publish any messages the client needs to
	Handle any incoming
disconnect the client
free any memory being used by the client
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <cstring>
#include <random>
#include "mqtt/async_client.h"

const std::string DFLT_SERVER_ADDRESS	{ "tcp://localhost:1883" };
//const std::string DFLT_SERVER_ADDRESS { "tcp://test.mosquitto.org:1883" };
//const std::string DFLT_CLIENT_ID		{ "async_publish_Sensor" };
const std::string PORT = "1883";
//const std::string TOPIC { "hello" };
//const char* LWT_PAYLOAD = "Last will and testament.";


class MQTT_Sensor {
	
	public:
	
		//=============== Constructor ===============
		
		~MQTT_Sensor() {}
		
		//constructor to initialize the needed values
		MQTT_Sensor(double lowEnd, double highEnd, std::string type, int modus, std::string client_id);
		
		
		//=============== Methods ===============
		
		//creates random value with the parameters as barriers
		double random_value(double lowEnd, double highEnd);
		
		char* getTime();
		
		//handles how the sendig of the messages should be handled
		void repeater(double lowEnd, double highEnd, int modus, std::string type);
		
		std::string build_message();
		
		
		int send_message();
		
		int initialize_client();
		
		//=============== Getter & Setter ===============
		
		const std::string get_type() { return type; }
		void set_type(std::string type) { this->type = type; }
		
		const double get_data() { return data; }
		void set_data(double data) { this->data = data; }
	
		const std::string get_client_id () { return client_id; }
		void set_client_id(std::string client_id) { this->client_id = client_id; }
		
		const std::string get_address() { return address; }
		void set_address(std::string address) { this->address = address; }
		
		const std::string get_topic() { return this->topic; }
		void set_topic(std::string topic) { this->topic = topic; }
		
		//const mqtt::async_client get_client() { return client; }
		//void set_client(mqtt::async_client client) {this->client = client; }
		
		char* get_date() { return now; }
	
		
	private:
	
		std::string type;
		std::string address;
		std::string client_id;
		std::string topic;
	
		char* now;
		double data;
		
		//mqtt::async_client client;
	
};

/////////////////////////////////////////////////////////////////////////////

/**
 * A callback class for use with the main MQTT client.
 */
class callback : public virtual mqtt::callback
{
public:
	void connection_lost(const std::string& cause) override {
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr tok) override {
		std::cout << "\tDelivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << std::endl;
	}
};

/////////////////////////////////////////////////////////////////////////////

/**
 * A base action listener.
 */
class action_listener : public virtual mqtt::iaction_listener
{
protected:
	void on_failure(const mqtt::token& tok) override {
		std::cout << "\tListener failure for token: "
			<< tok.get_message_id() << std::endl;
	}

	void on_success(const mqtt::token& tok) override {
		std::cout << "\tListener success for token: "
			<< tok.get_message_id() << std::endl;
	}
};

/////////////////////////////////////////////////////////////////////////////

/**
 * A derived action listener for publish events.
 */
class delivery_action_listener : public action_listener
{
	std::atomic<bool> done_;

	void on_failure(const mqtt::token& tok) override {
		action_listener::on_failure(tok);
		done_ = true;
	}

	void on_success(const mqtt::token& tok) override {
		action_listener::on_success(tok);
		done_ = true;
	}

public:
	delivery_action_listener() : done_(false) {}
	bool is_done() const { return done_; }
};

/////////////////////////////////////////////////////////////////////////////





