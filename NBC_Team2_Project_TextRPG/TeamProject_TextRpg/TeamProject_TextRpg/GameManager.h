#pragma once
#include "Character.h"
#include "MonsterSpawner.h"
#include <string>
class Character;
class Monster;

enum class BattleResult
{
	PlayerWin,
	PlayerLose
};


class GameManager
{
public:
	void Run();

private:

	// === 게임 플로우 ===

	// 게임 시작
	void StartGame();

	// 플레이어 입력 로직
	void PlayerInputLogic();

	// 캐릭터 생성
	void CreateCharacter();

	// 플레이어 상태창
	void PlayerStatus();

	// 몬스터 생성
	void SpawnMonster();
	void GetMonster(int Level);

	// 전투 로직
	BattleResult Battle();

	// 보상 시스템
	void GiveReward();

	// 레벨 10인지 판단
	bool IsLevel10();

	// 상점 방문
	void OpenShop();

	// === 게임 유틸 ===

	void DisplayInventory(Character* player);

private:
	Character* player_;
	std::string name_;
	Monster* curMons_ = nullptr;
	MonsterSpawner mobSpawn_;
};

