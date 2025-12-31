#pragma once
#include "Creature.h"
#include <iostream>
#include <string>

class Character : public Creature
{
public:

	//호출 시 캐릭터 이름 변경 및 인스턴스 생성
	Character(std::string& name);
	//캐릭터 명 부적합 판정
	bool IsValidName();
	//호출 시 경험치 획득(전투 승리 시)
	bool GainExp(int Exp);
	//최대 레벨 판정
	bool IsMaxLv() const;
	void Attack();

private:
	static Character* instance;

	//TODO : 멤버변수 뒤 언더바
	int Hp = 200;
	int MaxHp = 200;
	int Atk = 30;
	int Lv = 1;
	int MaxLv = 10;
	int Exp = 0;
	int Point = 0;
	std::string CharacterName;
	
};

