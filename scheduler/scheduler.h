#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <chrono>
#include <map>
#include <string>

class MsgSched {
public:
	void add(std::chrono::system_clock::time_point timestamp,
			 const std::string& message);
	void wait_for_message();

private:
	std::multimap<std::chrono::system_clock::time_point, std::string> m_messages;
};

#endif /* SCHEDULER_H_ */
