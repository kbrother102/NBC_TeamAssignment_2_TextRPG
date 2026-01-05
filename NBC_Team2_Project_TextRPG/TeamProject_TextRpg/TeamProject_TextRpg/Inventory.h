#pragma once
#include "Item.h"
#include <vector>
#include <memory>

class Item;
class StatComponent;

class Inventory
{
public:
	bool AddItem(std::unique_ptr<Item> item);
	bool UseItem(int index, StatComponent& stats_);

	//int GetGold() const;
	//void AddGold(int amount);
	//bool SpendGold(int amount);

	std::string GetItemName(int index) const;
	bool IsEmptySlot(int index) const;
	
	void SellItem();

	int GetItemCount() const;
	const Item* GetItem(int index) const;

private:
	std::vector<std::unique_ptr<Item>> items_;
	//int Gold_ = 0;
};