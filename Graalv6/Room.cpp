#include "Room.h"



void Room::RoomInit()
{
	for (int i = 0; i < 4; i++)
	{
		walls[i] = 0;
		light = true;
	}
}

void Room::AddToStash(Item & item)
{
	stash.push_back(item);
}

int Room::CheckStash(std::string itemtype_compare)
{
	for (int i = 0; i < stash.size(); i++)
	{
		if (stash[i].itemtype == itemtype_compare)
		{
			return i;
		}
	}
	return -1;
}

Item Room::PassFromStash(int itemposition)
{
	return stash[itemposition];
}

void Room::RemoveFromStash(int itemposition)
{
	stash.erase(stash.begin() + itemposition);
}

void Room::OpenDoor(int dir)
{
	walls[dir] = 1;
}

Room::Room()
{
}


Room::~Room()
{
}
