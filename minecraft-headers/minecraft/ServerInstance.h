#pragma once

#include <minecraft/Minecraft.h>

class ServerInstance {

public:

    char filler[0xC];
    Minecraft* minecraft;
    char filler2[0x200];
};
