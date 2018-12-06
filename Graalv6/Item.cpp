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
}

Item::Item()
{
}


Item::~Item()
{
}
