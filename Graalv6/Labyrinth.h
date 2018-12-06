#pragma once
#include "Room.h"
#include <vector>

class Labyrinth
{
public:
	std::vector<Room> rooms; // room position in vector = x + width * y
	int width;
	int height;
	void SetWidth(int x);
	void SetHeight(int y);
	bool CheckWidth();
	bool CheckHeight();
	void LabCreation(int x, int y);
	void OpenSide(int position, int dir);
	Labyrinth();
	~Labyrinth();
};

