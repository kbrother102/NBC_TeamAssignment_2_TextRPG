#include "Inventory.h"
#include "Item.h"

bool Inventory::AddItem(std::unique_ptr<Item> item)
{
	if (!item) return false;
	items_.push_back(std::move(item));
	return true;
}

bool Inventory::UseItem(int index, StatComponent& stats)
{
	if (index < 0 || index >= items_.size()) return false;

	if (items_[index]->Use(stats))
	{
		items_.erase(items_.begin() + index);
		return true;
	}
	return false;
}