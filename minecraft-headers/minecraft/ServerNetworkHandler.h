#pragma once

struct NetworkStats {
	int32_t filler, ping, avgping, maxbps;
	float packetloss, avgpacketloss;
};

class NetworkPeer {
	public:
		virtual ~NetworkPeer();
		virtual void sendPacket();
		virtual void receivePacket();
		virtual NetworkStats getNetworkStatus(void);
};

class NetworkHandler {
	public:
		NetworkPeer &getPeerForUser(NetworkIdentifier const &);
};

class ServerNetworkHandler : NetworkHandler {
	public:
		void disconnectClient(NetworkIdentifier const &, std::string const &, bool);
		ServerPlayer *_getServerPlayer(NetworkIdentifier const &, unsigned char);
};
