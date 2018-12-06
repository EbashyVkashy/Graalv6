#pragma once
#include "Model.h"

class Printer
{
public:
	void Welcome();
	void Rules();
	void AskWidth();
	void AskHeight();
	void YourCommand();
	void NoDoor();
	void NoSuchCommand();
	void NoSuchItem();
	void NoSuchFood();
	void RoomStatus(Model &);
	void DarkRoomStatus();
	void OnlyMove();
	Printer();
	~Printer();
};

