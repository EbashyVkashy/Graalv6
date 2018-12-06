#pragma once
#include "Item.h"
#include <vector>
#include <string>

class Player
{
public:
	int position; // first setting in model.GenerateLevel()
	int initial_life;
	int life;
	std::vector<Item> inventory;
	void PlayerInit(int x, int y);
	void AddToInventory(Item &);
	int CheckInventory(std::string itemname_compare);
	Item PassFromInv(int itemposition);
	void RemoveFromInv(int itemposition);
	void Move(int dir, int x);
	Player();
	~Player();
};

