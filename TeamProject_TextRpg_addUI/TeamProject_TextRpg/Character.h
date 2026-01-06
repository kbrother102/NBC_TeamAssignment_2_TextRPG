#pragma once
#include "Creature.h"
#include <string>
#include <memory>
//사용 할 두 클래스 전방 선언
class Inventory;
class StatComponent;
class Action;

class Character : public Creature
{	//스태틱 따로 분류
public:
	//Create를 통해서만 생성하게 변경
	static std::unique_ptr<Character> Create(const std::string& name);
	//캐릭터 명 부적합 판정
	static bool IsValidName(const std::string& name);

public:
	//호출 시 캐릭터 이름 변경 및 인스턴스 생성
	//Character(const std::string& name);
	// 크리쳐 타입 추가
	std::string GetType() override;
	//생성자 스텟 묶음 분리
	void StartCharacterStat(int Level);
	//호출 시 경험치 획득(전투 승리 시)
	//void GainExp(int amount);
	//피격 함수
	void TakeDamage(int dmg) override;
	//아이템 사용 함수
	bool UseItem(int index); //player.UseItem(0); 으로 사용 호출 가능.
	//골드 변경
	void ChangeGold(int amount);
	//골드 획득
	//void GainGold(int amount);
	//골드 사용
	//void SpendGold(int amount);

	StatComponent* GetStatComponent() override;
	Inventory* GetInventory();
	const Inventory* GetInventory() const;

	Action* GetAction();
	const Action* GetAction() const;

	//Reward 연계 함수
	void AddExp(int amount);
	//void AddGold(int amount); //상단의 ChangeGold로 병합

	//공격 함수
	int GetAttack() const;
	//최대 레벨 판정
	bool IsMaxLv() const;
	//사망 판정 함수
	bool IsDead() const;

	//게터 함수들
	int GetHp() const;
	int GetMaxHp() const;
	int GetAtk() const;
	int GetLv() const;
	int GetExp() const;

	//TODO: MAXEXP 추가
	int GetMaxExp() const;
	int GetGold() const;
	std::string GetName() const;// override;

	explicit Character(const std::string& name);
private:
	std::string CharacterName_;
	std::unique_ptr<Inventory> inventory_;
	std::unique_ptr<StatComponent> stats_;
	std::unique_ptr<Action> action_;

	//StatComponent쪽 수정이 확인되면 아래는 주석 예정
	//int Hp_ = 200;
	//int MaxHp_ = 200;
	//int Atk_ = 30;
	//int Lv_ = 1;
	//int MaxLv_ = 10;
	//int Exp_ = 0;
	//int Point_ = 0;
};