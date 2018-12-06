#pragma once
#include <vector>
#include "Item.h"
#include <string>

class Room
{
public:
	int walls[4]; // 0-West, 1-North, 2-East, 3-South
	std::vector<Item> stash;
	bool light; // 0-no light, 1-light
	void RoomInit();
	void AddToStash(Item &item);
	int CheckStash(std::string itemtype_compare);
	Item PassFromStash(int itemposition);
	void RemoveFromStash(int itemposition);
	void OpenDoor(int dir);
	Room();
	~Room();
};

