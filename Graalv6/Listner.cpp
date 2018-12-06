#include "Listner.h"
#include <iostream>


int Listner::ListenSize()
{
	int temp = 0;
	scanf_s("%i", &temp);
	while ((getchar()) != '\n');
	return temp;
}

std::string Listner::ListenCommand()
{
	std::string string_toreturn;
	std::getline(std::cin, string_toreturn);
	return string_toreturn;
}

Listner::Listner()
{
}


Listner::~Listner()
{
}
