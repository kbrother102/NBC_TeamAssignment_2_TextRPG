#pragma once
class Action
{
	void Attack(); 
	

	void PickUpItem(Item* item);
	


private:
	Character* character = nullptr;
	Monster* monster = nullptr;
	Inventory* inventory = nullptr;
};

