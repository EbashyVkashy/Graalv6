#pragma once
#include "Listner.h"
#include <string>

class Commands
{
public:
	std::string lastcommand_value;
	Listner listner;
	int GetSize();
	int GetCommand();
	std::string ReturnCommandValue();
	Commands();
	~Commands();
};

