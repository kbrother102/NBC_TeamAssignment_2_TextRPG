#include <iostream>
#include "GameManager.h"
#include "MonsterSpawner.h"
#include "Random.h"
#include "StatComponent.h"
#include "Action.h"
#include "Inventory.h"
#include "RewardManager.h"

void GameManager::Run()
{
	// 0번 키를 누르면 게임 종료
	while ()
	{
		StartGame();
		PlayerInputLogic();
		CreateCharacter();
		GenerateMonster();
		Battle();
		
		if ((Battle() == BattleResult::PlayerLose())) continue;
	}
}

void GameManager::StartGame()
{
	std::cout << "게임 시작" << std::endl;
}

void GameManager::PlayerInputLogic()
{
	std::cout << "이름을 입력해주세요 : ";
	std::cin >> name_;
}

void GameManager::CreateCharacter()
{
	player_ = new Character(name_);
	std::cout << "생성된 이름: " << player_->GetName();
}

void GameManager::GenerateMonster()
{
	MonsterSpawner MonsterSpawner;
	MonsterSpawner.Spawn(mobBox_);
}

BattleResult GameManager::Battle()
{
	curMons_ = GenerateMonster(player_->GetLv()); // player의 레벨? monster의 레벨?

	Action playeraction;
	playeraction.SetOwner(player);

	Action monsteraction;
	monsteraction.SetOwner(monster);

	while (player_->!IsDead())
	{
		playeraction.Attack(curMons_);
		if (curMons_->DieMob()) break;

		monsteraction.Attack(player_);
	}

	if (player_->!IsDead())
	{
		std::cout << "전투 승리, 보상을 받으세요." << std::endl;
		GiveReward();
		return BattleResult::PlayerWin;
	}
	else
	{
		std::cout << "전투 패배, 메인으로 돌아갑니다." << std::endl;
		return BattleResult::PlayerLose;
	}

}

void GameManager::GiveReward()
{
	RewardManager::GetInstance().ProcessReward();
}

bool GameManager::IsLevel10()
{
	return true;
}

bool GameManager::OpenShop()
{
	return true;
}

Monster* GameManager::GenerateMonster(int Level)
{
	curMons_ = mobBox_[Random::GetRandInt(0, 1)];
	curMons_->SpawnMob(level);
	return curMons_;
}

void GameManager::DisplayInventory(Character* player)
{
}
