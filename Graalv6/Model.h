#pragma once
#include "Labyrinth.h"
#include "Player.h"

class Model
{
public:
	Player player;
	Labyrinth labyrinth;
	int lastmovedirection;
	void Move(int dir);
	int CheckMove(std::string dir);
	int CheckGet(std::string item_toget);
	int CheckDrop(std::string item_todrop);
	bool CheckOpen();
	void TransferToInventory(int position);
	void TransferToStash(int position);
	int NumberOfDoors();
	int PlayerXpos();
	int PlayerYpos();
	bool WestDoor();
	bool NorthDoor();
	bool EastDoor();
	bool SouthDoor();
	int ItemsInStash();
	std::string ReturnItemName(int position);
	void GenerateLevel();
	void SetPlayerValues();
	Model();
	~Model();
};

