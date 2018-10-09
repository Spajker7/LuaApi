#pragma once
#include <minecraft/Player.h>

struct LuaPlayer {
  Player& player;

  std::string getName() {
    return player.getNameTag();
  }
};
