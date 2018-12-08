#include "Model.h"
#include "Printer.h"
#include "Commands.h"
#include "RoomScenes.h"

int main()
{
	Model model;
	Commands commands;
	Printer printer;
	RoomScenes roomscenes;
	
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

	while (model.ReturnPlayerLife() > 0 && victoryflag == false)
	{
		enum room_type {STANDARDROOM = 0, DARKROOM = 1, MONSTERROOM = 2};
		int temp = model.RoomTypeReturn();
		switch (temp)
		{
		case STANDARDROOM:
			roomscenes.StandardRoom(model, commands, printer, victoryflag);
			break;
		case DARKROOM:
			roomscenes.DarkRoom(model, commands, printer, victoryflag);
			break;
		case MONSTERROOM:
			roomscenes.MonsterRoom(model, commands, printer, victoryflag);
		default:
			break;
		}
	}
	
	if (victoryflag == true)
	{
		printer.Victory();
	}
	if (model.player.life == 0)
	{
		printer.Death();
	}
	system("pause");
}
