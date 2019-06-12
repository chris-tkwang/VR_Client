#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"

class ClientGame
{
public:
	ClientGame(void);
	~ClientGame(void);

	ClientNetwork* network;

	void sendActionPackets();

    char network_data[MAX_PACKET_SIZE];

    void update();

	std::pair<int, int> my_attack = std::make_pair(-1,-1);
	std::pair<int, int> other_attack = std::make_pair(-1, -1);
	std::pair<int, int> my_damage = std::make_pair(-1, -1);
	std::pair<int, int> other_damage = std::make_pair(-1, -1);
	glm::mat4 my_headPose = glm::mat4(1.0f);
	glm::mat4 other_headPose = glm::mat4(1.0f);

	bool game_mode = false;

	bool my_done = false;
	bool other_done = false;
};

