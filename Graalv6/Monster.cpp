#include "Monster.h"



void Monster::CreateMonster()
{
	int temp = rand() % 3;
	switch (temp)
	{
	case 0:
		monstername = "gigant rat";
		break;
	case 1:
		monstername = "skeleton";
		break;
	case 2:
		monstername = "your boss";
		break;
	default:
		break;
	}
}

Monster::Monster()
{
}


Monster::~Monster()
{
}
