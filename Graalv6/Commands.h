#pragma once
#include "Listner.h"

class Commands
{
public:
	std::string lastcommand_value;
	Listner listner;
	int GetSize();
	int GetCommand();
	int GetCommandWithTimer();
	std::string ReturnCommandValue();
	Commands();
	~Commands();
};

