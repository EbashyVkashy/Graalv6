#include "Labyrinth.h"

#include <iostream>
void Labyrinth::SetWidth(int x)
{
	width = x;
}

void Labyrinth::SetHeight(int y)
{
	height = y;
}

bool Labyrinth::CheckWidth()
{
	if (width > 3 && width < 51)
	{
		return true;
	}
	return false;
}

bool Labyrinth::CheckHeight()
{
	if (height > 3 && height < 51)
	{
		return true;
	}
	return false;
}

void Labyrinth::LabCreation(int x, int y)
{
	width = x;
	height = y;
	for (int i = 0; i < x; i ++)
		for (int j = 0; j < y; j++)
		{
			Room temp;
			temp.RoomInit();
			rooms.push_back(temp);
		}
}

void Labyrinth::OpenSide(int position, int dir) // dir 0 - west 1 - north 2 - east 3 - south
{
	if ((position / width == 0 && dir == 3) || (position / width == height - 1 && dir == 1) || (position % width == 0 && dir == 0) || (position % width == width - 1 && dir == 2)) // borderline exeptions
	{
		return;
	}
	rooms[position].OpenDoor(dir);
	switch (dir)
	{
	case 0:
		rooms[position - 1].OpenDoor(2);
		break;
	case 1:
		rooms[position + width].OpenDoor(3);
		break;
	case 2:
		rooms[position + 1].OpenDoor(0);
		break;
	case 3:
		rooms[position - width].OpenDoor(1);
		break;
	default:
		break;
	}
}

Labyrinth::Labyrinth()
{
}


Labyrinth::~Labyrinth()
{
}
