#include "Character.h"
#include <iostream>

//Charactor::Charactor(const std::string &name)
//{
//
//}

//전투 완료시 경험치 획득 호출
bool Character::GainExp(int exp)
{	//최고 레벨 판정 함수 추가예정
	//경험치 획득
	Exp += exp;
	//레벨업 체크
	while (Exp >= 100 && Lv < MaxLv)
	{
		Exp -= 100;
		Lv++;
		MaxHp += Lv * 20;
		Atk += Lv * 5;
		Hp = MaxHp;
	}
}