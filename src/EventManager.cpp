#include "EventManager.h"
#include <string>
#include <modloader/log.h>
#include "sol.hpp"

using namespace modloader;

void EventManager::registerEventCallback(std::string name, sol::function function) {
	eventCallbacks[name].push_back(function);
}

void EventManager::callEventCallbacks(std::string const &name, LuaPlayer& arg)
{
	auto itr = eventCallbacks.find(name);
	if (itr != end(eventCallbacks))
	{
		std::vector<sol::function> * events = &eventCallbacks[name];

		for (sol::function &event : *events)
		{
			event(arg);
		}
	}

}
