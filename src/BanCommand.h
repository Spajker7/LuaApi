#include <minecraft/command/Command.h>
#include <minecraft/command/CommandMessage.h>
#include <minecraft/command/CommandOutput.h>
#include <minecraft/command/CommandParameterData.h>
#include <minecraft/command/CommandRegistry.h>
#include <minecraft/command/CommandVersion.h>
#include <minecraft/Player.h>
#include <minecraft/ServerInstance.h>
#include <minecraft/Minecraft.h>
#include <modloader/log.h>
#include <string>

#include <climits>

using namespace modloader;

extern ServerInstance* serverInstance;

class CommandSelectorBase {
  int filler[0x90];
  CommandSelectorBase(bool isPlayer);
  public:
  std::shared_ptr<std::vector<Actor *>> newResults(CommandOrigin const &) const;
};

template <typename T> class CommandSelector : public CommandSelectorBase {
  public:
  CommandSelector();
};

class BanCommand : public Command {

public:
	//BanCommand();
	CommandSelector<Player> target;

	~BanCommand() override = default;
	
	static void setup(CommandRegistry& registry) {
		Log::info("LeetApi", "Registering command");
		registry.registerCommand("ban", "Bans a player", (CommandPermissionLevel) 1, (CommandFlag) 0, (CommandFlag) 0);
		Log::info("LeetApi", "Registering overload");
		registry.registerOverload<BanCommand>("ban", CommandVersion(0, INT32_MAX), CommandParameterData(type_id<CommandRegistry, CommandSelector<Player>>(), &CommandRegistry::parse<CommandSelector<Player>>, "target", (CommandParameterDataType)0, nullptr, offsetof(BanCommand, target), false, -1));
		Log::info("LeetApi", "Done");
	}
	
	BanCommand() {}

	void execute(CommandOrigin const& origin, CommandOutput& outp) override {
		Log::info("LeetApi", "Executing command");

		auto res = target.newResults(origin);
		Log::info("LeetApi", "1");
		if (!res->empty())
		{
	  		for (auto ent : *res) {
				auto player = dynamic_cast<ServerPlayer *>(ent);
				if (player) {
					//banPlayer(&ent->uuid, "Banned");
					//kickPlayer(ent);
					outp.addMessage("§4Banned " + player->getNameTag());
				}
		  	}
		}

		outp.success();
	}

};


