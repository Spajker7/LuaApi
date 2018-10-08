#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "BlockSourceListener.h"

class Player;

enum class DimensionId;

class Level : public BlockSourceListener {

public:
    Player * getPlayer(std::string const&) const;
    std::vector<std::unique_ptr<Player>>& getUsers();
};
