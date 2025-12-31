#pragma once

class Action
{
public:
	//플레이어 결정.
	void SetCharacter(Character* c) { character_ = c; }
	//소유자 결정.
	void SetOwner(Creature* owner) { owner_ = owner; };
	//공격.
	void Attack(Creature* target);
	//아이템 랜덤 사용.
	void RandUseItem(Item* Item, Inventory* inventory);

	//데미지 받기.
	//void TakeDamage(int dmg);

private:
	Creature* owner_ = nullptr;
	Character* character_ = nullptr;


	
};

