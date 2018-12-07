#pragma once
#include "Model.h"
#include "Printer.h"
#include "Commands.h"

class RoomScenes
{
private:
	enum command_type { ERROR = 0, MOVE = 1, GET = 2, DROP = 3, OPEN = 4, EAT = 5, GETGOLD = 6, DROPGOLD = 7, NOTINTIME = 8 };
	void Move(Model &, Commands &, Printer &, bool &victoryflag);
	void Get(Model &, Commands &, Printer &, bool &victoryflag);
	void Drop(Model &, Commands &, Printer &, bool &victoryflag);
	void Open(Model &, Commands &, Printer &, bool &victoryflag);
	void Eat(Model &, Commands &, Printer &, bool &victoryflag);
	void GetGold(Model &, Commands &, Printer &, bool &victoryflag);
	void DropGold(Model &, Commands &, Printer &, bool &victoryflag);
	void NotInTime(Model &, Commands &, Printer &, bool &victoryflag);
public:
	void StandardRoom(Model &, Commands &, Printer &, bool &victoryflag);
	void DarkRoom(Model &, Commands &, Printer &, bool &victoryflag);
	void MonsterRoom(Model &, Commands &, Printer &, bool &victoryflag);
	RoomScenes();
	~RoomScenes();
};

