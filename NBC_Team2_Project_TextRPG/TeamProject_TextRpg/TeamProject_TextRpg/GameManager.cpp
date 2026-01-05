#include <iostream>
#include "GameManager.h"
#include "Monster.h"
#include "MonsterSpawner.h"
#include "Random.h"
#include "StatComponent.h"
#include "Action.h"
#include "Inventory.h"
#include "RewardManager.h"
#include "Logger.h"
#include "Shop.h"

void GameManager::Run()
{
	StartGame();
	PlayerInputLogic();
	CreateCharacter();
	while (true)
	{
		BattleResult result = Battle();

		if ((result == BattleResult::PlayerLose)) continue;
	}
}


//TODO : cout을 Logger::Add("메시지 출력"); 로 변경
void GameManager::StartGame()
{
	Logger::Add(LogType::INFO, "게임시작");
}

void GameManager::PlayerInputLogic()
{
	Logger::Add(LogType::INFO, "이름을 입력해주세요 : ");
	std::cin >> name_;
}

void GameManager::CreateCharacter()
{
	player_ = new Character(name_);
	std::string nickname = "생성된 캐릭터 이름: " + player_->GetName();
	Logger::Add(LogType::INFO, nickname);

}

void GameManager::SpawnMonster()
{
	curMons_ = mobSpawn_.Spawn();
}

void GameManager::GetMonster(int Level)
{
	if (curMons_ == nullptr) SpawnMonster();
	if (curMons_ != nullptr) curMons_->SpawnMob(Level);
}

BattleResult GameManager::Battle()
{
	// 플레이어 레벨에 맞춰 몬스터 생성
	GetMonster(player_->GetLv());

	// 플레이어, 몬스터가 모두 살아있을 때 루프 반복
	while (!player_->IsDead() && !curMons_->GetIsDead())
	{
		// 플레이어 -> 몬스터 공격
		player_->GetAction()->Attack(curMons_);

		// 몬스터 사망
		if (curMons_->GetIsDead())
		{
			curMons_->GetActionComponent()->Die();
			break;
		}

		// 몬스터 -> 플레이어 공격
		curMons_->GetActionComponent()->Attack(player_);

		// 플레이어 사망
		if (player_->IsDead())
		{
			player_->GetAction()->Die();
			break;
		}
	}

	if (!(player_->IsDead()))
	{
		Logger::Add(LogType::INFO, "전투에서 승리했습니다! 보상을 받으세요");
		GiveReward();
		return BattleResult::PlayerWin;
	}
	else
	{
		Logger::Add(LogType::INFO, "전투에서 패배했습니다. 메인으로 돌아갑니다.");
		return BattleResult::PlayerLose;
	}

}

void GameManager::GiveReward()
{
	RewardManager::GetInstance().ProcessReward(curMons_, player_);
}

bool GameManager::IsLevel10()
{
	return true;
}

bool GameManager::OpenShop()
{
	return true;
}

void GameManager::DisplayInventory(Character* player)
{
}
