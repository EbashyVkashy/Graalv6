#pragma once
#include <string>
class Item
{
public:
	std::string itemtype;
	std::string itemname;
	int gold_quantity;
	void CreateItem(std::string itemtype_tocreate);
	void SetStartGold(int start_gold);
	int GoldQuantity();
	void AddGold(int quantity);
	Item();
	~Item();
};

