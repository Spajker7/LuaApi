#pragma once

#include <memory>

class NetworkIdentifier;

class Actor {
	public:
		const std::string &getNameTag() const;
		virtual ~Actor();
};

struct Mob : public Actor {
};

class Player : public Mob {
public:
    NetworkIdentifier const& getClientId() const;
    unsigned char getClientSubId() const;
};

class ServerPlayer : public Player {

public:
    void disconnect();

};
