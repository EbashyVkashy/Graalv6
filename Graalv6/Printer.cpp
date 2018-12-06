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
		}
	}
	std::cout << std::endl;
}

Printer::Printer()
{
}


Printer::~Printer()
{
}