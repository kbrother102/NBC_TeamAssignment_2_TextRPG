#pragma once
#include "Character.h"
#include "MonsterSpawner.h"
#include "UIManager.h"  //TODO: UIManager 추가
#include <string>
class Character;
class Monster;

enum class BattleResult
{
	PlayerWin,
	PlayerLose,
	GameClear,
	ExitGame
};


class GameManager
{
public:
	GameManager();  // TODO: [추가] 생성자
	~GameManager(); // TODO: [추가] 소멸자
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

	// 상점 방문
	void OpenShop();

	// === 게임 유틸 ===

	void DisplayInventory(Character* player);

	// TODO: [추가] 화면 갱신용 UI 함수 (전투 중 계속 호출)
	void UpdateDisplay();

private:
	Character* player_;
	std::string name_;
	Monster* curMons_ = nullptr;
	MonsterSpawner mobSpawn_;

	// TODO: [UI] UI 매니저 선언
	UIManager* uiManager_;
};

