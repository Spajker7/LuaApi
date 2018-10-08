#include <modloader/statichook.h>
#include <modloader/log.h>
#include <minecraft/Player.h>
#include "../LuaPlayer.cpp"
#include "../EventManager.h"
#include <minecraft/ServerNetworkHandler.h>

EventManager& getEventManager();

TInstanceHook(void, _ZN20ServerNetworkHandler24onReady_ClientGenerationER6PlayerRK17NetworkIdentifier, ServerNetworkHandler, ServerPlayer &player, NetworkIdentifier const &nid) {
  LuaPlayer luaPlayer{.player = player};

  getEventManager().callEventCallbacks("PlayerJoin", luaPlayer);
}
