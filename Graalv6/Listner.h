#pragma once
#include <string>

class Listner
{
public:
	int ListenSize();
	std::string ListenCommand();
	std::string ListenCommandWithTimer();
	Listner();
	~Listner();
};

