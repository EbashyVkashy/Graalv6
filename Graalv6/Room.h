#pragma once
#include <vector>
#include "Item.h"
#include "Monster.h"
#include <string>

class Room
{
public:
	int walls[4]; // 0-West, 1-North, 2-East, 3-South
	std::vector<Item> stash;
	Monster monster;
	bool monsterexistence;
	bool light; // 0-no light, 1-light
	void RoomInit();
	void AddToStash(Item &item);
	int CheckStash(std::string itemname_compare);
	Item PassFromStash(int itemposition);
	void RemoveFromStash(int itemposition);
	void LightOff();
	void AddMonster(Monster &);
	std::string ReturnMonsterName();
	void OpenDoor(int dir);
	void AddGold(Item &gold_toadd);
	Room();
	~Room();
};

