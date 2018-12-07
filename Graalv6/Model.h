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
	void PlayerGotHit();
	int RoomTypeReturn();
	int ReturnGoldQuantity(int position);
	bool WestDoor();
	bool NorthDoor();
	bool EastDoor();
	bool SouthDoor();
	int ReturnBackDirection();
	std::string ReturnMonsterName();
	int ItemsInStash();
	std::string ReturnItemName(int position);
	void Eat(int stash_position);
	void GenerateLevel();
	void SetPlayerValues();
	void GoldToInv(int position);
	void GoldToStash(int position);
	Model();
	~Model();
};

