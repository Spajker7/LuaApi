#pragma once

#include <string>
#include <map>
#include <vector>
#include "sol.hpp"

class EventManager {
	private:
		std::map<std::string, std::vector<sol::function>> eventCallbacks;
	public:
		void registerEventCallback(std::string name, sol::function function) {
			eventCallbacks[name].push_back(function);
		}

		template<typename... Args>
		void callEventCallbacks(std::string name, Args... args) {

			auto itr = eventCallbacks.find(name);
			if (itr != end(eventCallbacks))
			{
				std::vector<sol::function> * events = &eventCallbacks[name];

				for (sol::function &event : *events)
				{
					event(args...);
				}
			}

		}
};
