#include "Model.h"
#include "Printer.h"
#include "Commands.h"

void StandardRoom(Model &, Commands &, Printer &, bool &victoryflag);
void DarkRoom(Model &, Commands &, Printer &);

int main()
{
	Model model;
	Commands commands;
	Printer printer;
	bool victoryflag = false;

	printer.Welcome();
	printer.Rules();

	do
	{
		printer.AskWidth();
		model.labyrinth.SetWidth(commands.GetSize());
	} while (model.labyrinth.CheckWidth() != true);
	do
	{
		printer.AskHeight();
		model.labyrinth.SetHeight(commands.GetSize());
	} while (model.labyrinth.CheckHeight() != true);

	model.GenerateLevel();
	model.SetPlayerValues();

	while (model.player.life > 0 && victoryflag == false)
	{
		enum room_type {STANDARDROOM = 0, DARKROOM = 1};
		int temp = model.RoomTypeReturn();
		switch (temp)
		{
		case STANDARDROOM:
			StandardRoom(model, commands, printer, victoryflag);
			break;
		case DARKROOM:
			DarkRoom(model, commands, printer);
			break;
		default:
			break;
		}
	}
}

void StandardRoom(Model &model, Commands &commands, Printer &printer,bool &victoryflag)
{
	enum command_type {ERROR = 0, MOVE = 1, GET = 2, DROP = 3, OPEN = 4, EAT = 5, GETGOLD = 6, DROPGOLD = 7};
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

void DarkRoom(Model &model, Commands &commands, Printer &printer)
{
	enum command_type { ERROR = 0, MOVE = 1, GET = 2, DROP = 3, OPEN = 4, EAT = 5, GETGOLD = 6, DROPGOLD = 7};
	int commandtype = 0;
	printer.DarkRoomStatus();
	printer.YourCommand();
	commandtype = commands.GetCommand();
	switch (commandtype)
	{
	case ERROR:
		printer.NoSuchCommand();
		break;
		return;
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
			return;
		}
	default:
		break;
	}
	printer.OnlyMove();
	return;
}