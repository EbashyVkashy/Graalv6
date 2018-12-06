#include "Item.h"



void Item::CreateItem(std::string itemtype_tocreate)
{
	itemtype = itemtype_tocreate;
	itemname = itemtype;
}

Item::Item()
{
}


Item::~Item()
{
}
