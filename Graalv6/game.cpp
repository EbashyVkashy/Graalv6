#include "Model.h"
#include "Printer.h"
#include "Commands.h"

void StandardRoom(Model &, Commands &, Printer &, bool &victoryflag);

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
		StandardRoom(model, commands, printer, victoryflag);
	}
}

void StandardRoom(Model &model, Commands &commands, Printer &printer,bool &victoryflag)
{
	enum command_type {ERROR = 0, MOVE = 1, GET = 2, DROP = 3, OPEN = 4};
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
	default:
		break;
	}
}