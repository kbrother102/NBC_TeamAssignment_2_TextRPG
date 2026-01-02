#pragma once

class Action
{
public:
	//소유자 결정.
	void SetOwner(Creature* owner) { owner_ = owner; };
	//공격.
	void Attack(Creature* target);
	//아이템 랜덤 사용.
	void RandUseItem(Inventory* inventory);
	//죽음.
	void Die();


private:
	Creature* owner_ = nullptr;


	
};

