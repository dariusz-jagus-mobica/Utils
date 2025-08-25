#include "scheduler.h"
#include <iostream>

void MsgSched::add(std::chrono::system_clock::time_point timestamp,
				   const std::string& message)
{
	m_messages.insert({timestamp, message});
}

void MsgSched::wait_for_message()
{
	while (!m_messages.empty()) {
		auto it_first = m_messages.begin();
		auto ts_first = it_first->first;
		auto msg_first = it_first->second;

		while (std::chrono::system_clock::now() < ts_first)
			continue;

		std::cout << msg_first << std::endl;
		m_messages.erase(it_first);
	}
}


