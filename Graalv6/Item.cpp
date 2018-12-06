#include "Item.h"



void Item::CreateItem(std::string itemtype_tocreate)
{
	itemtype = itemtype_tocreate;
	itemname = itemtype;
	if (itemtype == "food")
	{
		int temp = rand() % 3;
		switch (temp)
		{
		case 0:
			itemname = "egg";
			break;
		case 1:
			itemname = "milk";
			break;
		case 2:
			itemname = "bread";
			break;
		default:
			break;
		}
	}
	if (itemtype == "gold")
	{
		gold_quantity = rand() % 500;
	}
}

void Item::SetStartGold(int start_gold)
{
	gold_quantity = start_gold;
}

int Item::GoldQuantity()
{
	return gold_quantity;
}

void Item::AddGold(int quantity)
{
	gold_quantity += quantity;
}

Item::Item()
{
}


Item::~Item()
{
}
