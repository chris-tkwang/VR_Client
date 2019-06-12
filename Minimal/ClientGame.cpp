
#include "ClientGame.h"


ClientGame::ClientGame(void)
{

    network = new ClientNetwork();

    // send init packet
    const unsigned int packet_size = sizeof(Packet);
    char packet_data[packet_size];

    Packet packet;
    packet.packet_type = INIT_CONNECTION;

    packet.serialize(packet_data);

    NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}


ClientGame::~ClientGame(void)
{
}

void ClientGame::sendActionPackets()
{
    // send action packet
    const unsigned int packet_size = sizeof(Packet);
    char packet_data[packet_size];

    Packet packet;
    packet.packet_type = ACTION_EVENT;

	packet.attack = my_attack;
	packet.damage = my_damage;
	packet.done = my_done;
	packet.headPose = my_headPose;

	my_attack.first = -1;
	my_attack.second = -1;
	my_damage.first = -1;
	my_damage.second = -1;
    packet.serialize(packet_data);

    NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientGame::update()
{
    Packet packet;
    int data_length = network->receivePackets(network_data);

    if (data_length <= 0) 
    {
        //no data recieved
        return;
    }

    int i = 0;
    while (i < (unsigned int)data_length) 
    {
        packet.deserialize(&(network_data[i]));
        i += sizeof(Packet);

        switch (packet.packet_type) {

            case ACTION_EVENT:

                //printf("client received action event packet from server\n");
				if (packet.attack.first != -1) {
					other_attack = packet.attack;
					game_mode = true;
				}

				if (packet.damage.first != -1) {
					other_damage = packet.damage;
				}

				other_done = packet.done;
				other_headPose = packet.headPose;

                sendActionPackets();

                break;

            default:

                printf("error in packet types\n");

                break;
        }
    }
}
