#include <modloader/statichook.h>
#include "BanCommand.h"
#include <minecraft/ServerInstance.h>
#include <modloader/log.h>
#include <string>
#include <limits.h>
#include <dirent.h>
#include <lua/lua.hpp>
#include "EventManager.h"
#include "sol.hpp"
#include "LuaPlayer.h"

using namespace modloader;

ServerInstance* serverInstance;
EventManager eventManager;
std::map<std::string, sol::state> modStates;



THook(void, _ZN9OpCommand5setupER15CommandRegistry, CommandRegistry& registry) {
	Log::info("LeetApi", "Sup");
	BanCommand::setup(registry);
	original(registry);
}

extern "C" int luaLog(lua_State* state)
{
	// The number of function arguments will be on top of the stack.
	int args = lua_gettop(state);
	char logline[512];
	logline[0] = 0;

	for ( int n=1; n<=args; ++n) {
		strcat(logline, lua_tostring(state, n));
	}

	Log::info("Lua", logline);

	// Let Lua know how many return values we've passed
	return 0;
}

void luaRegisterEvent(sol::table tbl, std::string name, sol::function function)
{
	eventManager.registerEventCallback(name, function);
	Log::info("Registred %s", name.c_str());
}

void loadMod(std::string const &name, std::string const &path) {
	Log::info("LuaModLoader", "Loading mod: %s", name.c_str());

	sol::state &lua = modStates[name];


	lua.open_libraries(sol::lib::base);
	lua.set_function("log", &luaLog);
	lua["EventManager"] = lua.create_table_with("registerEvent", &luaRegisterEvent);

	lua.new_usertype<LuaPlayer>("LuaPlayer",
		"getName", &LuaPlayer::getName
	);

	sol::load_result script = lua.load_file(path.c_str());
	sol::protected_function_result scriptResult = script();

	if(!scriptResult.valid()) {
		sol::error err = scriptResult;
		std::string what = err.what();
		Log::error("LuaModLoader", "Error loading %s: %s", name.c_str(), what.c_str());
	}
}

void loadModsFromDirectory(std::string const &path) {
	Log::info("LuaModLoader", "Loading mods from directory: %s", path.c_str());
	DIR* dir = opendir(path.c_str());
	dirent* ent;
	if (dir == nullptr) {
		Log::info("LuaModLoader", "Directory does not exist");
		return;
	}

	while ((ent = readdir(dir)) != nullptr) {
		if (ent->d_name[0] == '.')
			continue;
		std::string fileName(ent->d_name);

		std::string filePath = path;
		filePath += fileName;

		loadMod(fileName, filePath);
	}

	closedir(dir);
	Log::info("LuaModLoader", "Loaded mods");
}

EventManager& getEventManager() {
	return eventManager;
}

extern "C" void modloader_on_server_start(ServerInstance * instance) {
	Log::info("LeetApi", "Sup2");
	serverInstance = instance;

	loadModsFromDirectory("luamods/");
}
