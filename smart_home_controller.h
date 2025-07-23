#include <string>
#include <mqtt/async_client.h>

class SmartHomeController {
public:
	SmartHomeController(const std::string& broker, const std::string& id);
	
	void connect();
	void disconnect();
	void sendCommand(const std::string& topic, const std::string& message);

private:
	std::string brokerAddress;
	std::string clientId;
	mqtt::async_client client;
};

/* Example use:
	SmartHomeController controller("tcp://localhost:1883", "SmartHomeClient");

	controller.connect();
	controller.sendCommand("home/livingroom/light", "ON");
	controller.sendCommand("home/thermostat", "22"); // Set temperature to 22C
	controller.disconnect();
*/
