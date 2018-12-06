#include "Model.h"
#include <iostream>

void Model::Move(int dir)
{
	lastmovedirection = dir;
	player.Move(dir, labyrinth.width);
}

int Model::CheckMove(std::string dir)
{
	if (dir == "W" && labyrinth.rooms[player.position].walls[0] == 1)
	{
		return 0;
	}
	if (dir == "N" && labyrinth.rooms[player.position].walls[1] == 1)
	{
		return 1;
	}
	if (dir == "E" && labyrinth.rooms[player.position].walls[2] == 1)
	{
		return 2;
	}
	if (dir == "S" && labyrinth.rooms[player.position].walls[3] == 1)
	{
		return 3;
	}
	return -1;
}

int Model::CheckGet(std::string item_toget)
{
	return labyrinth.rooms[player.position].CheckStash(item_toget); // -1 if no item.
}

int Model::CheckDrop(std::string item_todrop)
{
	return player.CheckInventory(item_todrop);
}

bool Model::CheckOpen()
{
	if (labyrinth.rooms[player.position].CheckStash("chest") < 0 || player.CheckInventory("key") < 0)
	{
		return false;
	}
	return true;
}



void Model::TransferToInventory(int position)
{
	Item item_topass = labyrinth.rooms[player.position].PassFromStash(position);
	player.AddToInventory(item_topass);
	labyrinth.rooms[player.position].RemoveFromStash(position);
}

void Model::TransferToStash(int position)
{
	Item item_topass = player.PassFromInv(position);
	labyrinth.rooms[player.position].AddToStash(item_topass);
	player.RemoveFromInv(position);
}

int Model::NumberOfDoors()
{
	int doors = 0;
	for (int i = 0; i < 4; i++)
	{
		if (labyrinth.rooms[player.position].walls[i] == 1)
		{
			doors += 1;
		}
	}
	return doors;
}

int Model::PlayerXpos()
{
	int tempx = (player.position % labyrinth.width);
	return tempx;
}

int Model::PlayerYpos()
{
	int tempy = (player.position / labyrinth.width);
	return tempy;
}

int Model::RoomTypeReturn()
{
	if (labyrinth.rooms[player.position].light == false && labyrinth.rooms[player.position].CheckStash("torch") < 0 && player.CheckInventory("torch") < 0)
	{
		return 1; // Dark room
	}
	return 0; //standard room;
}

int Model::ReturnGoldQuantity(int position)
{
	int temp = labyrinth.rooms[player.position].stash[position].gold_quantity;
	return temp;
}

bool Model::WestDoor()
{
	if (labyrinth.rooms[player.position].walls[0] == 1)
	{
		return true;
	}
	return false;
}

bool Model::NorthDoor()
{
	if (labyrinth.rooms[player.position].walls[1] == 1)
	{
		return true;
	}
	return false;
}

bool Model::EastDoor()
{
	if (labyrinth.rooms[player.position].walls[2] == 1)
	{
		return true;
	}
	return false;
}

bool Model::SouthDoor()
{
	if (labyrinth.rooms[player.position].walls[3] == 1)
	{
		return true;
	}
	return false;
}

int Model::ItemsInStash()
{
	int quantity = labyrinth.rooms[player.position].stash.size();
	return quantity;
}

void Model::GoldToInv(int position)
{
	Item item_topass;
	item_topass = labyrinth.rooms[player.position].PassFromStash(position);
	int temp_gold = item_topass.GoldQuantity();
	labyrinth.rooms[player.position].RemoveFromStash(position);
	int pos_inventory = player.CheckInventory("gold");
	std::cout << std::endl << pos_inventory;
	player.AddGold(temp_gold, pos_inventory);
}

void Model::GoldToStash(int position)
{
	Item item_topass;
	item_topass = player.PassFromInv(position);
	labyrinth.rooms[player.position].AddGold(item_topass);
	player.LoseGold(position);
}

std::string Model::ReturnItemName(int position)
{
	return labyrinth.rooms[player.position].stash[position].itemname;
}

void Model::Eat(int stash_position)
{
	labyrinth.rooms[player.position].RemoveFromStash(stash_position);
	player.RestoreLife();
}

void Model::GenerateLevel() // Building labyrinth - core obj - doors - setting player initial position
{
	const int ammount_doors = labyrinth.width * labyrinth.height;
	const int ammount_torches = (labyrinth.width * labyrinth.height) / 2;
	const int ammount_darkrooms = (labyrinth.width * labyrinth.height) / 3;
	const int ammount_food = (labyrinth.width * labyrinth.height) / 2;
	const int ammount_gold = (labyrinth.width * labyrinth.height) / 2;

	labyrinth.LabCreation(labyrinth.width, labyrinth.height); // initializing labyrinth

	player.position = std::rand() % (labyrinth.width * labyrinth.height); // setting player initial position
	
	Item item_toadd;   // adding key & and chest in room stash
	int keypos = -1;
	item_toadd.CreateItem("key");
	do
	{
		keypos = rand() % (labyrinth.width * labyrinth.height);
	} while (keypos == player.position);
	labyrinth.rooms[keypos].AddToStash(item_toadd);
	item_toadd.CreateItem("chest");
	int chestpos = -1;
	do
	{
		chestpos = rand() % (labyrinth.width * labyrinth.height);
	} while (chestpos == keypos || chestpos == player.position);
	labyrinth.rooms[chestpos].AddToStash(item_toadd);
		// adding path between enter, key and chest
	int temp_pos = player.position;  //enter and key | if enter above | 0-west 1-north 2-east 3-south
	if (temp_pos > keypos)
	{
		while (temp_pos > keypos && (temp_pos - labyrinth.width) >= 0)
		{
			labyrinth.OpenSide(temp_pos, 3);
			temp_pos -= labyrinth.width;
		}
		while (temp_pos > keypos)
		{
			labyrinth.OpenSide(temp_pos, 0);
			temp_pos -= 1;
		}
		while (temp_pos < keypos)
		{
			labyrinth.OpenSide(temp_pos, 2);
			temp_pos += 1;
		}
	}
	if (temp_pos < keypos)  // enter and key | if enter lower
	{
		while ((temp_pos - labyrinth.width) < keypos && (temp_pos - labyrinth.width) <= (labyrinth.width * labyrinth.height))
		{
			labyrinth.OpenSide(temp_pos, 1);
			temp_pos += labyrinth.width;
		}
		while (temp_pos < keypos)
		{
			labyrinth.OpenSide(temp_pos, 2);
			temp_pos += 1;
		}
		while (temp_pos > keypos)
		{
			labyrinth.OpenSide(temp_pos, 0);
			temp_pos -= 1;
		}
	}

	temp_pos = player.position; //enter and chest | if enter above  | 0-west 1-north 2-east 3-south
	if (temp_pos > chestpos)
	{
		while (temp_pos > chestpos && (temp_pos - labyrinth.width) >= 0)
		{
			labyrinth.OpenSide(temp_pos, 3);
			temp_pos -= labyrinth.width;
		}
		while (temp_pos > chestpos)
		{
			labyrinth.OpenSide(temp_pos, 0);
			temp_pos -= 1;
		}
		while (temp_pos < chestpos)
		{
			labyrinth.OpenSide(temp_pos, 2);
			temp_pos += 1;
		}
	}
	if (temp_pos < chestpos)  // enter and chest | if enter lower 
	{
		while (temp_pos - labyrinth.width < chestpos && (temp_pos + labyrinth.width) <= (labyrinth.width * labyrinth.height))
		{
			labyrinth.OpenSide(temp_pos, 1);
			temp_pos += labyrinth.width;
		}
		while (temp_pos < chestpos)
		{
			labyrinth.OpenSide(temp_pos, 2);
			temp_pos += 1;
		}
		while (temp_pos > chestpos)
		{
			labyrinth.OpenSide(temp_pos, 0);
			temp_pos -= 1;
		}
	}

	for (int i = 0; i < ammount_doors; i++) //add random doors
	{
		int temp = 0;
		temp = rand() % (labyrinth.height * labyrinth.width);
		labyrinth.OpenSide(temp, rand() % 4);
	}

	for (int i = 0; i < ammount_torches; i++) //add torches
	{
		int temp = 0;
		item_toadd.CreateItem("torch");
		temp = rand() % (labyrinth.height * labyrinth.width);
		labyrinth.rooms[temp].AddToStash(item_toadd);
	}
	for (int i = 0; i < ammount_darkrooms; i++) //add dark rooms
	{
		int temp = 0;
		temp = rand() % (labyrinth.height * labyrinth.width);
		labyrinth.rooms[temp].LightOff();
	}
	for (int i = 0; i < ammount_food; i++) //add food
	{
		int temp = 0;
		item_toadd.CreateItem("food");
		temp = rand() % (labyrinth.height * labyrinth.width);
		labyrinth.rooms[temp].AddToStash(item_toadd);
	}
	for (int i = 0; i < ammount_gold; i++) //add gold
	{
		int temp = 0;
		item_toadd.CreateItem("gold");
		temp = rand() % (labyrinth.height * labyrinth.width);
		labyrinth.rooms[temp].AddToStash(item_toadd);
	}
}

void Model::SetPlayerValues()
{
	player.PlayerInit(labyrinth.width, labyrinth.height);
}



Model::Model()
{
}


Model::~Model()
{
}

