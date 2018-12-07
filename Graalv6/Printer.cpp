#include "Printer.h"
#include <iostream>
#include <string>

void Printer::Welcome()
{
	std::cout << "Welcome traveler! You are about to enter great Labyrinth of the Holy Graal!" << std::endl;
}

void Printer::Rules()
{
	std::cout << "Rules: to move use W (west), N (north), E (east), S (south)." << std::endl;
	std::cout << "To get item - 'get [item]', to drop - 'drop [item]'" << std::endl;
	std::cout << "To open chest - 'open' (you need to have key in your inventory to open)" << std::endl;
	std::cout << "Use 'eat [food]' - to restore 10% of your life" << std::endl;
	std::cout << "Use 'fight' - to fight a monster (you need to have a sword in your inventory" << std::endl;
}
void Printer::AskWidth()
{
	std::cout << "Please enter width of the Labyrinth (4 to 50): ";
}

void Printer::AskHeight()
{
	std::cout << "Please enter height of the Labyrinth (4 to 50): ";
}

void Printer::YourCommand()
{
	std::cout << "Your command: ";
}

void Printer::NoDoor()
{
	std::cout << "There is no door!" << std::endl;
}

void Printer::NoSuchCommand()
{
	std::cout << "No such command." << std::endl;
}

void Printer::NoSuchItem()
{
	std::cout << "There is no such item." << std::endl;
}

void Printer::NoSuchFood()
{
	std::cout << "The is no such food." << std::endl;
}

void Printer::RoomStatus(Model & model)
{
	std::cout << "You are in the room [" << model.PlayerXpos() << "." << model.PlayerYpos() << "]. There are [" << model.NumberOfDoors() << "] doors";
	if (model.WestDoor() == true)
	{
		std::cout << " west";
	}
	if (model.NorthDoor() == true)
	{
		std::cout << " north";
	}
	if (model.EastDoor() == true)
	{
		std::cout << " east";
	}
	if (model.SouthDoor() == true)
	{
		std::cout << " south";
	}
	std::cout << ". ";
	int items_number = model.ItemsInStash();
	if (items_number == 0)
	{
		std::cout << "No items in this room.";
	}
	else
	{
		std::cout << "Items in this room:";
		for (int i = 0; i < items_number; i++)
		{
			std::cout << " " << model.ReturnItemName(i);
			if (model.ReturnItemName(i) == "gold")
			{
				std::cout << " " << model.ReturnGoldQuantity(i);
			}
		}
	}
	std::cout << std::endl;
}

void Printer::EvilMonster(Model &model)
{
	std::string temp = model.ReturnMonsterName();
	std::cout << "There is an evil " << temp << " in the room!" << std::endl;
}

void Printer::DarkRoomStatus()
{
	std::cout << "Can`see anything in this dark place!" << std::endl;
}

void Printer::OnlyMove()
{
	std::cout << "You can only move in dark room." << std::endl;
}

void Printer::NoGold()
{
	std::cout << "There is no gold!" << std::endl;
}

void Printer::FailOnCommand()
{
	std::cout << "You failed the command, lost 10% hp and moved to previous room." << std::endl;
}

void Printer::SuccesLoseLife()
{
	std::cout << "You successed the command, but lost 10% hp and moved to previous room." << std::endl;
}

void Printer::MoveLoseLife()
{
	std::cout << "You moved, but lost 10% hp ." << std::endl;
}

void Printer::SuccesOnCommand()
{
	std::cout << "You successed the command." << std::endl;
}

void Printer::NotInTime()
{
	std::cout << "You were to slow!" << std::endl;
}

void Printer::Death()
{
	std::cout << "You found your death in this labirynth!" << std::endl;
}

void Printer::Victory()
{
	std::cout << "You found Holy Graal, congratulations!" << std::endl;
}

void Printer::NoSword()
{
	std::cout << "You have no sword." << std::endl;
}

void Printer::MonsterKilled()
{
	std::cout << "You killed monster." << std::endl;
}

void Printer::CouldntKill()
{
	std::cout << "Couldnt kill monster. Lost 10% of hp and moved to previous room." << std::endl;
}

void Printer::NoMonster()
{
	std::cout << "There is no monster." << std::endl;
}


Printer::Printer()
{
}


Printer::~Printer()
{
}
