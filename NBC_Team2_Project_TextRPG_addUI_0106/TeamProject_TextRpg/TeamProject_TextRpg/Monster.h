#pragma once
#include "Creature.h"
#include "Action.h"
#include "StatComponent.h"
#include <string>

class Action;
class StatComponent;

class Monster : public Creature
{
public:
	//getter
		//string
	virtual std::string GetName() const = 0;
	//int
	virtual int GetHealth() const = 0;

	//TODO GetMaxHealth 추가
	virtual int GetMaxHealth() const = 0;

	virtual int GetAttack() const = 0;
	virtual int GetGold() const = 0;
	virtual int GetExp() const = 0;
	//bool
	virtual bool GetIsDead() const = 0;
	//component
	virtual StatComponent* GetStatComponent() = 0;
	virtual Action* GetActionComponent() = 0;

	virtual void TakeDamage(int dmg) = 0;
	virtual void SpawnMob(int level) = 0;
	virtual void UseSkill() = 0;
	virtual void GetDie() = 0;
	virtual void PlayerKillText();

	// TODO: [UI] 이미지 경로 Getter/Setter 추가
	std::string GetImagePath() const { return imagePath_; }
	void SetImagePath(std::string path) { imagePath_ = path; }

	// TODO: 몬스터 이미지 경로용 생성자 초기화
	Monster() : imagePath_("") {}


	~Monster()
	{
		delete monStat_;
	}

protected:
	StatComponent* monStat_ = new StatComponent();

	// TODO: 이미지 경로 변수 추가
	std::string imagePath_;
};