#pragma once

#include <memory>

class CommandOrigin;
class CommandOutputSender;

enum class MCCATEGORY {
    //
};

struct MCRESULT {
    bool success;
    MCCATEGORY category;
    unsigned short code;
};

class MinecraftCommands {

public:


};
