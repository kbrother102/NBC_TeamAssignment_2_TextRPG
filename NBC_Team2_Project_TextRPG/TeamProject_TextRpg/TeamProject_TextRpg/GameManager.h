#pragma once
class Character;
class Monster;

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

	// 몬스터 생성
	void GenerateMonster();

	// 전투 로직
	void Battle(Character* player);

	// 보상 시스템
	void GiveReward();

	// 레벨 10인지 판단
	bool IsLevel10();

	// 상점 방문
	bool OpenShop();

	// 게임 종료
	void GameOver();

	// === 게임 유틸 ===

	Monster* GenerateMonster(int Level);
	void DisplayInventory(Character* player);

private:
	Character* player_;
	Monster* monster_;

};

