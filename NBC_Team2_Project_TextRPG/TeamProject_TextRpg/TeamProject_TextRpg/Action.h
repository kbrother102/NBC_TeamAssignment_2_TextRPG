#pragma once
class Action
{
	
	void Attack(); 
	

	void UseItem(Item* Item, Character* character);
	


private:
	//TODO : 멤버변수 뒤에는 언더바
	class Character* character = nullptr;
	Monster* monster = nullptr;
	Inventory* inventory = nullptr;
	//TODO : 액션은 캐릭터와 몬스터를 사용하지 않는다(매개변수로 받음).  멤버변수 필요없음
	//TODO : 이 액션컴포넌트를 가지는 주인 등록하기 (생성시에 받음)
};

