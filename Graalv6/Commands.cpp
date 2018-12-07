#include "Commands.h"
#include <ctime>


int Commands::GetSize()
{
	int value = listner.ListenSize();
	return value;
}
int Commands::GetCommand() // 8 - reserved for GetCommandWIthTimer();
{
	int lastcommand_type = 0;
	lastcommand_value = listner.ListenCommand();
	if (lastcommand_value == "W" || lastcommand_value == "N" || lastcommand_value == "E" || lastcommand_value == "S") // type - MOVE
	{
		lastcommand_type = 1; // type - MOVE
		return lastcommand_type;
	}
	if (lastcommand_value == "get gold") // CRUCIAL! MUST BE BEFORE "get " - check
	{
		lastcommand_type = 6;
		lastcommand_value = lastcommand_value.substr(4, lastcommand_value.length());
		return lastcommand_type;
	}
	if (lastcommand_value == "drop gold") // CRUCIAL! MUST BE BEFORE "drop " - check
	{
		lastcommand_type = 7;
		lastcommand_value = lastcommand_value.substr(5, lastcommand_value.length());
		return lastcommand_type;
	}
	if (lastcommand_value.substr(0, 4) == "get ") // CRUCIAL! MUST BE AFTER "get gold"  - check
	{
		lastcommand_type = 2; 
		lastcommand_value = lastcommand_value.substr(4, lastcommand_value.length());
		return lastcommand_type;
	}
	if (lastcommand_value.substr(0, 5) == "drop ")// CRUCIAL! MUST BE AFTER "drop gold " - check
	{
		lastcommand_type = 3; 
		lastcommand_value = lastcommand_value.substr(5, lastcommand_value.length());
		return lastcommand_type;
	}
	if (lastcommand_value == "open")
	{
		lastcommand_type = 4;
		return lastcommand_type;
	}
	if (lastcommand_value.substr(0, 4) == "eat ")
	{
		lastcommand_type = 5;
		lastcommand_value = lastcommand_value.substr(4, lastcommand_value.length());
		return lastcommand_type;
	}
	return lastcommand_type; //0 - type - ERROR
}

int Commands::GetCommandWithTimer()
{
	const int time_tofail = 5000;
	clock_t timer;
	timer = clock();
	int toreturn = GetCommand();
	if ((clock() - timer < time_tofail))
	{
		toreturn = 8; //8 - not in time ERROR
	}
	return GetCommand();
}

std::string Commands::ReturnCommandValue()
{
	return lastcommand_value;
}

Commands::Commands()
{
}


Commands::~Commands()
{
}
