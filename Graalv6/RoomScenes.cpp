#include "RoomScenes.h"
#include <iostream>


void RoomScenes::StandardRoom(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	int commandtype = 0;
	printer.RoomStatus(model);
	printer.YourCommand();
	commandtype = commands.GetCommand();
	switch (commandtype)
	{
	case ERROR:
		printer.NoSuchCommand();
		break;
	case MOVE:
		Move(model, commands, printer, victoryflag);
		break;
	case GET:
		Get(model, commands, printer, victoryflag);
		break;
	case DROP:
		Drop(model, commands, printer, victoryflag);
		break;
	case OPEN:
		Open(model, commands, printer, victoryflag);
		break;
	case EAT:
		Eat(model, commands, printer, victoryflag);
		break;
	case GETGOLD:
		GetGold(model, commands, printer, victoryflag);
		break;
	case DROPGOLD:
		DropGold(model, commands, printer, victoryflag);
		break;
	default:
		break;
	}
}

void RoomScenes::DarkRoom(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	int commandtype = 0;
	printer.DarkRoomStatus();
	printer.YourCommand();
	commandtype = commands.GetCommand();
	switch (commandtype)
	{
	case ERROR:
		printer.NoSuchCommand();
		break;
	case MOVE:
		Move(model, commands, printer, victoryflag);
		break;
	default:
		printer.OnlyMove();
		break;
	}
}

void RoomScenes::MonsterRoom(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	enum COMMANDSUCCESS { FAIL = 0, GOTHIT = 1, SUCCESS = 2 };
	int commandtype = 0;
	printer.RoomStatus(model);
	printer.EvilMonster(model);
	printer.YourCommand();
	commandtype = commands.GetCommand();
	int commandsuccess = rand() % 3; // 0 - fail, 1 - success but forced back, 2 - full success
	switch (commandsuccess)
	{
	case FAIL:
	{
		MoveBack(model, commands, printer, victoryflag);
		LoseHp(model, commands, printer, victoryflag);
		printer.FailOnCommand();
		return;
		break;
	}
	case GOTHIT:
	{
		if (commandtype != MOVE)
		{
			printer.SuccesLoseLife();
		}
		break;
	}
	case SUCCESS:
		printer.SuccesOnCommand();
		break;
	default:
		break;
	}
	switch (commandtype)
	{
	case ERROR:
		break;
	case MOVE:
	{
		if (commandsuccess == GOTHIT)
		{
			printer.MoveLoseLife();
		}
		Move(model, commands, printer, victoryflag);
		return;
		break;
	}
	case GET:
		break;
	case DROP:
		break;
	case OPEN:
		break;
	case EAT:
		break;
	case GETGOLD:
		break;
	case DROPGOLD:
		break;
	default:
		break;
	}
	if (commandsuccess == GOTHIT)
	{
		MoveBack(model, commands, printer, victoryflag);
		LoseHp(model, commands, printer, victoryflag);
	}
}

RoomScenes::RoomScenes()
{
}


RoomScenes::~RoomScenes()
{
}

void RoomScenes::Move(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	int way = model.CheckMove(commands.ReturnCommandValue());
	if (way == -1) // -1 return value if no door
	{
		printer.NoDoor();
		return;
	}
	model.Move(way);
}

void RoomScenes::Get(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	int stash_pointer = model.CheckGet(commands.ReturnCommandValue());
	if (stash_pointer == -1) // -1 return value if no item
	{
		printer.NoSuchItem();
		return;
	}
	model.TransferToInventory(stash_pointer);
}

void RoomScenes::Drop(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	int inventory_pointer = model.CheckDrop(commands.ReturnCommandValue());
	if (inventory_pointer == -1) // -1 return value if no item
	{
		printer.NoSuchItem();
		return;
	}
	model.TransferToStash(inventory_pointer);
}

void RoomScenes::Open(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	if (model.CheckOpen() == false)
	{
		return;
	}
	victoryflag = true;
}

void RoomScenes::Eat(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	int stash_pointer = model.CheckGet(commands.ReturnCommandValue());
	if (stash_pointer == -1)
	{
		printer.NoSuchFood();
		return;
	}
	model.Eat(stash_pointer);
}

void RoomScenes::GetGold(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	int stash_pointer = model.CheckGet(commands.ReturnCommandValue());
	if (stash_pointer == -1) // -1 return value if no item
	{
		printer.NoGold();
		return;
	}
	model.GoldToInv(stash_pointer);
}

void RoomScenes::DropGold(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	int inventory_pointer = model.CheckDrop(commands.ReturnCommandValue());
	if (inventory_pointer == -1) // -1 return value if no item
	{
		printer.NoGold();
		return;
	}
	model.GoldToStash(inventory_pointer);
}

void RoomScenes::NotInTime(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
}

void RoomScenes::LoseHp(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	model.PlayerGotHit();
}

void RoomScenes::MoveBack(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	int backdir;
	backdir = model.ReturnBackDirection();
	model.Move(backdir);
}
