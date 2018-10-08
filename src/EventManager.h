#pragma once

#include <string>
#include <map>
#include <vector>
#include "sol.hpp"
#include "LuaPlayer.cpp"

class EventManager {
	public:
		void registerEventCallback(std::string name, sol::function function);
		void callEventCallbacks(std::string const &name, LuaPlayer& arg);
	private:
		std::map<std::string, std::vector<sol::function>> eventCallbacks;

};
