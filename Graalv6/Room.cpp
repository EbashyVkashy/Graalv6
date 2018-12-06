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

int Room::CheckStash(std::string itemname_compare)
{
	for (int i = 0; i < stash.size(); i++)
	{
		if (stash[i].itemname == itemname_compare)
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

void Room::LightOff()
{
	light = false;
}

void Room::OpenDoor(int dir)
{
	walls[dir] = 1;
}

void Room::AddGold(Item &gold_toadd)
{
	int temp = CheckStash("gold");
	if (temp == -1)
	{
		AddToStash(gold_toadd);
		return;
	}
	int temp_goldquantity = gold_toadd.gold_quantity;
	stash[temp].AddGold(temp_goldquantity);
}

Room::Room()
{
}


Room::~Room()
{
}
