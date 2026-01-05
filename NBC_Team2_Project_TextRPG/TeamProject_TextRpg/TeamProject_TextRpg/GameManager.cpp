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
#include "Console.h"

void GameManager::Run()
{
	while (true)
	{
		StartGame();
		PlayerInputLogic();
		CreateCharacter();
		while (true)
		{
			BattleResult result = Battle();

			if ((result == BattleResult::PlayerLose))
			{
				delete player_;
				player_ = nullptr;
				break;
			}
			DisplayInventory(player_);
			OpenShop();
		}
	}
}

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

void GameManager::OpenShop()
{
	Logger::Add(LogType::INFO, "상점에 진입하시겠습니까? (1: 예 / 2: 아니오)");
	int input;
	Console::Input(input);

	if (input == 1)
	{
		Shop shop;
		shop.RunShop(player_);
	}
}

void GameManager::DisplayInventory(Character* player)
{
	Logger::Add(LogType::INFO, "인벤토리를 확인하시겠습니까? (1: 예 / 2: 아니오)");

	int input;
	Console::Input(input);

	if (input == 1)
	{
		// 재화 정보
		int currentGold = player_->GetStatComponent()->GetGold();
		Logger::Add("보유 골드: " + std::to_string(currentGold) + " G");

		// 아이템 정보
		Inventory* inventory = player_->GetInventory();
		int itemCount = inventory->GetItemCount();

		if (itemCount == 0)
		{
			Logger::Add("가방이 비어 있습니다.");
		}
		else
		{
			for (int i = 0; i < itemCount; ++i)
			{
				std::string itemName = inventory->GetItemName(i);
				Logger::Add(std::to_string(i + 1) + ". " + itemName);
			}
		}
	}
}

