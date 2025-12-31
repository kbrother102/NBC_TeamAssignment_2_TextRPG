#pragma once
class Action
{
	
	void Attack();
	

	void RandUseItem(Item* Item, Inventory* inventory);
	
	void AddItem(Item* item);
	void TakeDamage(int dmg);

private:
	Creature* owner_ = nullptr;
};

