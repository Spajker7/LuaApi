#pragma once

#include <minecraft/level/Level.h>

class MinecraftCommands;
class NetworkIdentifier;

class Minecraft {

public:

    MinecraftCommands* getCommands();
    Level* getLevel() const;
    void disconnectClient(NetworkIdentifier const&,std::string const&);

};
