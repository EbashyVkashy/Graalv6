#pragma once
#include <string>
class Item
{
public:
	std::string itemtype;
	std::string itemname;
	void CreateItem(std::string itemtype_tocreate);
	Item();
	~Item();
};

