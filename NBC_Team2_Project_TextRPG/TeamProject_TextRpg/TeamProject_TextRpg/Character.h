#pragma once
#include "Creature.h"
#include <iostream>
#include <string>
//사용 할 두 클래스 전방 선언
class Inventory;
class StatComponent;

class Character : public Creature
{
public:
	//호출 시 캐릭터 이름 변경 및 인스턴스 생성
	Character(const std::string& name);
	//캐릭터 명 부적합 판정
	static bool IsValidName(const std::string& name);
	//호출 시 경험치 획득(전투 승리 시)
	bool GainExp(int Exp);
	//최대 레벨 판정
	bool IsMaxLv() const;
	//공격 함수
	int Attack();
	//피격 함수
	void TakeDamage(int dmg);
	//사망 판정 함수
	bool IsDead() const;
	//아이템 사용 함수
	bool UseItem(int index); //player.UseItem(0); 으로 사용 호출 가능.

	//게터 함수들
	int GetHp() const;// { return StatComponent_.GetHp(); }
	int GetMaxHp() const;// { return StatComponent_.GetMaxHp(); }
	int GetAtk() const;// { return StatComponent_.GetAtk(); }
	int GetLv() const;// { return StatComponent_.GetLv(); }
	int GetExp() const; //{ return StatComponent_.GetExp(); }
	int GetPoint() const; //{ return StatComponent_.GetPoint(); }
	std::string GetName() const; //{ return name_; }

private:
	std::string CharacterName_;
	//Inventory inventory_;
	//StatComponent쪽 수정이 확인되면 주석 제거 예정
	//StatComponent stats_;
	//StatComponent쪽 수정이 확인되면 아래는 주석 예정
	int Hp_ = 200;
	int MaxHp_ = 200;
	int Atk_ = 30;
	int Lv_ = 1;
	int MaxLv_ = 10;
	int Exp_ = 0;
	int Point_ = 0;

};