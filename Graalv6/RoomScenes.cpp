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
	case FIGHT:
	{
		if (FightPossibility(model, commands, printer, victoryflag) == true)
		{
			KillMonster(model, commands, printer, victoryflag);
		}
		break;
	}
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
	commandtype = commands.GetCommandWithTimer();
	int commandsuccess = rand() % 3; // 0 - fail, 1 - success but forced back, 2 - full success
	if (commandsuccess == FAIL)
	{
		MoveBack(model, commands, printer, victoryflag);
		LoseHp(model, commands, printer, victoryflag);
		printer.FailOnCommand();
		return;
	}
	switch (commandtype)
	{
	case ERROR:
		printer.NoSuchCommand();
		return;
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
	case NOTINTIME:
		printer.NotInTime();
		MoveBack(model, commands, printer, victoryflag);
		LoseHp(model, commands, printer, victoryflag);
		return;
		break;
	case FIGHT:
	{
		if (FightPossibility(model, commands, printer, victoryflag) == true)
		{
			switch (commandsuccess)
			{
			case GOTHIT:
				printer.CouldntKill();
				MoveBack(model, commands, printer, victoryflag);
				LoseHp(model, commands, printer, victoryflag);
				return;
				break;
			case SUCCESS:
				KillMonster(model, commands, printer, victoryflag);
				printer.MonsterKilled();
				return;
				break;
			default:
				break;
			}
		}
		break;
	}
	default:
		break;
	}
	switch (commandsuccess)
	{
	case SUCCESS:
		printer.SuccesOnCommand();
		break;
	case GOTHIT:
	{
		printer.SuccesLoseLife();
		MoveBack(model, commands, printer, victoryflag);
		LoseHp(model, commands, printer, victoryflag);
		break;
	}
	default:
		break;
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

bool RoomScenes::FightPossibility(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	if (model.labyrinth.rooms[model.ReturnPlayerPos()].monsterexistence == false)
	{
		printer.NoMonster();
		return false;
	}
	if (model.AskForSword() == false)
	{
		printer.NoSword();
		return false;
	}
	return true;
}

void RoomScenes::KillMonster(Model &model, Commands &commands, Printer &printer, bool &victoryflag)
{
	model.DeleteMonster();
}
