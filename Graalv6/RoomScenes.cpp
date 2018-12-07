#include "RoomScenes.h"



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
	{
		int way = model.CheckMove(commands.ReturnCommandValue());
		if (way == -1) // -1 return value if no door
		{
			printer.NoDoor();
			return;
		}
		model.Move(way);
		break;
	}
	case GET:
	{
		int stash_pointer = model.CheckGet(commands.ReturnCommandValue());
		if (stash_pointer == -1) // -1 return value if no item
		{
			printer.NoSuchItem();
			return;
		}
		model.TransferToInventory(stash_pointer);
		break;
	}
	case DROP:
	{
		int inventory_pointer = model.CheckDrop(commands.ReturnCommandValue());
		if (inventory_pointer == -1) // -1 return value if no item
		{
			printer.NoSuchItem();
			return;
		}
		model.TransferToStash(inventory_pointer);
		break;
	}
	case OPEN:
	{
		if (model.CheckOpen() == false)
		{
			return;
		}
		victoryflag = true;
		break;
	}
	case EAT:
	{
		int stash_pointer = model.CheckGet(commands.ReturnCommandValue());
		if (stash_pointer == -1)
		{
			printer.NoSuchFood();
			return;
		}
		model.Eat(stash_pointer);
		break;
	}
	case GETGOLD:
	{
		int stash_pointer = model.CheckGet(commands.ReturnCommandValue());
		if (stash_pointer == -1) // -1 return value if no item
		{
			printer.NoGold();
			return;
			break;
		}
		model.GoldToInv(stash_pointer);
		break;
	}
	case DROPGOLD:
	{
		int inventory_pointer = model.CheckDrop(commands.ReturnCommandValue());
		if (inventory_pointer == -1) // -1 return value if no item
		{
			printer.NoGold();
			return;
			break;
		}
		model.GoldToStash(inventory_pointer);
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
