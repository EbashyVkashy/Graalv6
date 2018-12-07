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
	void EvilMonster(Model &);
	void DarkRoomStatus();
	void OnlyMove();
	void NoGold();
	void FailOnCommand();
	void SuccesLoseLife();
	void MoveLoseLife();
	void SuccesOnCommand();
	void NotInTime();
	void Death();
	void Victory();
	Printer();
	~Printer();
};

