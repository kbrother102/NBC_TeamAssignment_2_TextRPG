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

// TODO: 입력대기, 출력지연용 함수 사용
#include <conio.h> // _getch() 사용
#include <windows.h> // Sleep() 사용

// TODO: 생성자 - 로그출력 딜레이 관리
// TODO: 생성자(생성자 함수 전체 추가됨) 에서 UI 매니저 생성 
GameManager::GameManager()
{
	uiManager_ = new UIManager();
	uiManager_->InitSystem();

	// TODO: 매개변수에 'int delay'를 추가 (LogDefines 에서 설정)
	Logger::OnLogAdded = [this](LogType type, int delay)
		{
			this->UpdateDisplay();

			if (delay > 0)
			{
				Sleep(delay);
			}
		};
}

// TODO: 소멸자(소멸자 함수 전체 추가됨) 에서 메모리 해제
GameManager::~GameManager()
{
	// 게임 매니저가 사라지면 더 이상 UI를 못 그리므로 연결 해제
	Logger::OnLogAdded = nullptr;

	if (uiManager_) delete uiManager_;
	if (player_) delete player_;
	if (curMons_) delete curMons_;
}

void GameManager::Run()
{
	// TODO: [UI] UI 초기화
	uiManager_->InitSystem();

	while (true)
	{
		StartGame();

		// TODO: [UI] 화면 클리어 추가
		system("cls");

		PlayerInputLogic();
		CreateCharacter();

		// TODO: [UI] 화면 클리어 추가
		system("cls");

		// TODO: 기존 스텟 주석처리
		// PlayerStatus();

		// TODO: UI 실행
		uiManager_->RenderGameUI();
		UpdateDisplay(); // 초기 스탯 표시

		while (true)
		{
			BattleResult result = Battle();

			if ((result == BattleResult::PlayerLose))
			{
				delete player_;
				player_ = nullptr;

				delete curMons_;
				curMons_ = nullptr;
				break;
			}
			bool chooseMenu = true;
			
			/* //TODO: 기존 변경전 메뉴 - 주석으로 변경
			while (chooseMenu)
			{
				Logger::Add(LogType::INFO, "\n======= 마을 정비 =======");
				Logger::Add(LogType::INFO, "1. 상태 확인 | 2. 인벤토리 | 3. 상점 | 4. 다음 전투 시작");


				int choice;
				Console::Input(choice);

				switch (choice)
				{
				case 1:
					PlayerStatus(); // 내 상태 출력
					break;
				case 2:
					DisplayInventory(player_); // 인벤토리 확인
					break;
				case 3:
					OpenShop(); // 상점 이용
					break;
				case 4:
					Logger::Add(LogType::INFO, "다음 전장으로 이동합니다.");
					chooseMenu = false; // 정비 루프를 빠져나감
					break;
				default:
					Logger::Add(LogType::WARNING, "잘못된 입력입니다.");
					break;
				}
			}
			*/


			//TODO: ui용 메뉴 추가
			while (chooseMenu)
			{
				// [변경] UI 메뉴 출력
				uiManager_->RenderVillageMenu(); 
				uiManager_->RenderLogs(); // 로그창 갱신

				// [변경] InputString으로 안전하게 입력 받기
				std::string input = uiManager_->InputString("선택하세요: ");

				// 입력값이 없으면 재시도
				if (input.empty()) continue;

				int choice = std::stoi(input); // 문자열 -> 정수 변환

				switch (choice)
				{
				case 1:
					PlayerStatus(); // 상태창 갱신
					break;
				case 2:
					DisplayInventory(player_);
					break;
				case 3:
					OpenShop();
					// 상점 갔다오면 UI가 지워졌을 수 있으니 다시 그림
					uiManager_->RenderGameUI();
					uiManager_->RenderStats(player_);
					break;
				case 4:
					Logger::Add(LogType::INFO, "던전으로 이동합니다...");
					chooseMenu = false;
					break;
				default:
					Logger::Add(LogType::WARNING, "잘못된 입력입니다.");
					break;
				}
			}


		}
	}
}

void GameManager::StartGame()
{
	// TODO: 기존 시작 메뉴
	// Logger::Add(LogType::INFO, "게임시작");

	// TODO: [변경] UI 매니저실행
	uiManager_->RenderTitleScreen();

	// 키 입력 대기 (아무 키나 누르면 넘어감)
	_getch();
}

void GameManager::PlayerInputLogic()
{
	// TORO: 기존 ui 시스템 주석처리
	// Logger::Add(LogType::INFO, "이름을 입력해주세요 : ");
	// std::cin >> name_;

	// TODO: [변경] 캐릭터 생성 화면 출력
	uiManager_->RenderCharacterCreate();

	// TODO: [변경] UI 깨짐 방지 입력 함수 사용
	// 텍스트 + x, y좌표 위치 (26번째줄)
	name_ = uiManager_->InputString("이름을 입력하세요: ", 75, 38);

}

// TODO: [UI} 화면 갱신을 처리 함수 추가
void GameManager::UpdateDisplay()
{
	uiManager_->RenderStats(player_);
	uiManager_->RenderMonsterStats(curMons_);
	uiManager_->RenderLogs();
}

void GameManager::CreateCharacter()
{
	player_ = new Character(name_);
	std::string nickname = "생성된 캐릭터 이름: " + player_->GetName();
	Logger::Add(LogType::INFO, nickname);
}

void GameManager::PlayerStatus()
{
	// TORO: 기존 ui 시스템 주석처리
	// Logger::Add(LogType::INFO,
	//	"이름: " + player_->GetName() +
	//	" | 체력: " + std::to_string(player_->GetStatComponent()->GetHp()) + "/" + std::to_string(player_->GetStatComponent()->GetMaxHp()) +
	//	" | 경험치: " + std::to_string(player_->GetStatComponent()->GetExp()) +
	//	" | 보유 골드: " + std::to_string(player_->GetStatComponent()->GetGold()) + "G"
	// );

	// TODO: [UI] 텍스트 로그 스텟박스 ui출력
	uiManager_->RenderStats(player_);
	Logger::Add(LogType::INFO, "상태 정보를 갱신했습니다.");
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

	// TODO [UI] 전투 메뉴창 잠금 (UI매니저 호출)
	// =========================================================
	uiManager_->RenderBattleMode();

	// TODO: [UI] 몬스터 이미지 출력
	if (curMons_ != nullptr)
	{
		uiManager_->RenderMonsterArt(curMons_->GetImagePath());
	}

	// TODO: [UI] 몬스터 스탯창 표시
	uiManager_->RenderMonsterStats(curMons_);
	UpdateDisplay();

	// 플레이어, 몬스터가 모두 살아있을 때 루프 반복
	while (!player_->IsDead() && !curMons_->GetIsDead())
	{

		// 플레이어 -> 몬스터 공격
		player_->GetAction()->RandUseItem();
		player_->GetAction()->Attack(curMons_);

		// TODO: [UI] 화면 갱신 (몬스터 체력 감소 확인)
		UpdateDisplay();

		// 몬스터 사망
		if (curMons_->GetIsDead())
		{
			curMons_->GetDie();

			//TODO: [UI] 몬스터 사망시 이미지 갱신 (몬스터 정보창 지우기)
			UpdateDisplay();

			break;
		}

		// 몬스터 -> 플레이어 공격
		curMons_->GetActionComponent()->Attack(player_);

		//TODO: [UI] 플레이어 스텟 갱신 (피격후 감소 hp)
		UpdateDisplay();

		// 플레이어 사망
		if (player_->IsDead())
		{
			player_->GetAction()->Die();
			break;
		}
	}

	// TODO: [UI] 전투 종료 처리 (몬스터 정보창 지우기)
	uiManager_->RenderMonsterArt("empty.txt");

	if (!(player_->IsDead()))
	{
		Logger::Add(LogType::INFO, "전투에서 승리했습니다! 보상을 받으세요");
		GiveReward();

		// TODO: [UI] 보상 후(골드/경험치) 스탯 갱신
		UpdateDisplay(); 

		return BattleResult::PlayerWin;
	}
	else
	{
		Logger::Add(LogType::INFO, "전투에서 패배했습니다. 메인으로 돌아갑니다.");

		// TODO: [UI] 사망후 대기
		UpdateDisplay();
		_getch(); // 입력대기

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
	Shop shop;
	// TODO: 기존 runshop 주석처리
	// shop.RunShop(player_);

	// TODO: [UI] uiManager 매개변수 추가
	shop.RunShop(player_, uiManager_);

}

void GameManager::DisplayInventory(Character* player)
{
	// 재화 정보
	int currentGold = player_->GetStatComponent()->GetGold();
	Logger::Add(LogType::INFO, "보유 골드: " + std::to_string(currentGold) + " G");

	// 아이템 정보
	Inventory* inventory = player_->GetInventory();
	int itemCount = inventory->GetItemCount();

	// TODO: [UI] 메인 패널에 인벤토리 목록 출력
	std::vector<std::string> invList;
	invList.push_back("[ 인벤토리 ]");
	invList.push_back(" ");


	if (itemCount == 0)
	{
		Logger::Add(LogType::INFO, "가방이 비어 있습니다.");
	}
	else
	{
		for (int i = 0; i < itemCount; ++i)
		{
			// TODO: 기존 인벤토리 주석처리
			// std::string itemName = inventory->GetItemName(i);
			// Logger::Add(std::to_string(i + 1) + ". " + itemName);

			// TODO: [UI] 아이템 목록 만들기
			invList.push_back(std::to_string(i + 1) + ". " + inventory->GetItemName(i));

		}
	}

	// TODO: [UI] 
	uiManager_->RenderMainPanel(" INVENTORY ", invList);   // 메인 화면 중앙에 출력
	uiManager_->InputString("아무 키나 누르면 돌아갑니다."); // 키 입력 대기 (확인용)

}

