#include "smart_home_controller.h"
#include <iostream>

SmartHomeController::SmartHomeController(const std::string& broker, const std::string& id)
	: brokerAddress(broker), clientId(id), client(broker, id) {}

void SmartHomeController::connect() {
	try {
		mqtt::connect_options connOpts;
		connOpts.set_clean_session(true);
		std::cout << "Connecting to MQTT broker at " << brokerAddress << "...\n";
		client.connect(connOpts)->wait();
		std::cout << "Connected.\n";
        } catch (const mqtt::exception& e) {
		std::cerr << "Connection failed: " << e.what() << '\n';
        }
}

void SmartHomeController::disconnect() {
	try {
		std::cout << "Disconnecting from broker...\n";
		client.disconnect()->wait();
		std::cout << "Disconnected.\n";
        } catch (const mqtt::exception& e) {
		std::cerr << "Disconnection failed: " << e.what() << '\n';
        }
}

void SmartHomeController::sendCommand(const std::string& topic, const std::string& message) {
	try {
		mqtt::message_ptr pubmsg = mqtt::make_message(topic, message);
		pubmsg->set_qos(1);
		client.publish(pubmsg)->wait_for(std::chrono::seconds(10));
		std::cout << "Message sent to topic '" << topic << "': " << message << '\n';
	} catch (const mqtt::exception& e) {
		std::cerr << "Publish failed: " << e.what() << '\n';
        }
}

