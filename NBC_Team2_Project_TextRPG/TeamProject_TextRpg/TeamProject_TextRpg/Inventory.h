#pragma once
#include <vector>
#include <memory>

class Item;
class StatComponent;

class Inventory
{
public:
	bool AddItem(std::unique_ptr<Item> item);
	bool UseItem(int index, StatComponent& stats_);
	/*
	int GetPoint() const;
	void AddPoint(int amount);
	bool SpendPoint(int amount);

	int GetItemCoount() const;
	const Item* GetItem(int index) const;
	*/
private:
	std::vector<std::unique_ptr<Item>> items_;
	//int point_ = 0;
};