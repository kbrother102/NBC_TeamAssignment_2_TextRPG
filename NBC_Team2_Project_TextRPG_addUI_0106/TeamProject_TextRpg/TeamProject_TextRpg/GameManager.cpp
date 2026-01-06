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

// TODO 입력 예외처리 ( 숫자대신 글자입력 방지 )
int SafeInput(UIManager* ui, std::string prompt, int min, int max)
{
	while (true)
	{
		std::string input = ui->InputString(prompt);

		if (input.empty()) continue; // 엔터만 치면 무시

		try
		{
			int value = std::stoi(input);
			if (value >= min && value <= max)
			{
				return value; // 정상 입력 시 반환
			}
			else
			{
				Logger::Add(LogType::WARNING, "잘못된 번호입니다. (" + std::to_string(min) + "~" + std::to_string(max) + ")");
			}
		}
		catch (...) // 문자가 섞여있거나 숫자가 너무 클 때
		{
			Logger::Add(LogType::WARNING, "숫자만 입력해 주세요.");
		}

		// 오류 메시지 출력 후 UI 갱신 (로그가 보이게)
		ui->RenderLogs();
	}
}

// TODO: 생성자 - 로그출력 딜레이 관리
// TODO: 생성자(생성자 함수 전체 추가됨) 에서 UI 매니저 생성 
// TODO: 소멸자(소멸자 함수 전체 추가됨) 에서 메모리 해제
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

GameManager::~GameManager()
{
	// 게임 매니저가 사라지면 더 이상 UI를 못 그리므로 연결 해제
	Logger::OnLogAdded = nullptr;

	if (uiManager_) delete uiManager_;
	if (player_) delete player_;
	if (curMons_) delete curMons_;
}

// ============게임 시작 =================

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

			if ((result == BattleResult::PlayerLose || result == BattleResult::GameClear))
			{
				delete player_;
				player_ = nullptr;

				delete curMons_;
				curMons_ = nullptr;
				break;
			}

			if (result == BattleResult::ExitGame)
			{
				delete player_;
				player_ = nullptr;

				delete curMons_;
				curMons_ = nullptr;
				return;
			}

			bool chooseMenu = true;

			//TODO: 기존 변경전 메뉴 - 주석으로 변경
			/*
			while (chooseMenu)
			{
				Logger::Add(LogType::INFO, "\n======= 2조 룸 =======");
				Logger::Add(LogType::INFO, "1. 상태 확인 | 2. 인벤토리 | 3. 포인트샵 | 4. 다음 튜터링 시작");


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
					Logger::Add(LogType::INFO, "다음 튜터실로 이동합니다.");
					chooseMenu = false; // 정비 루프를 빠져나감
					break;
				default:
					Logger::Add(LogType::WARNING, "잘못된 입력입니다.");
					break;
				}
			}
			*/
			//====================================

			//TODO: ui용 메뉴 추가
			while (chooseMenu)
			{
				// [변경] UI 메뉴 출력
				uiManager_->RenderVillageMenu();
				uiManager_->RenderLogs(); // 로그창 갱신

				// SafeInput을 사용하여 안전하게 숫자 입력 받기
				// 문자를 입력해도 프로그램이 멈추지 않고 경고 메시지를 띄웁니다.
				int choice = SafeInput(uiManager_, "선택하세요: ", 1, 4);

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
					Logger::Add(LogType::INFO, "튜터룸으로 이동합니다...");
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
	// TODO: 기존 시작 메뉴 주석처리
	// Logger::Add(LogType::INFO, "캠프 시작");

	// TODO: [변경] UI 매니저실행
	while (true)
	{
		// 1. 타이틀 화면 그리기
		uiManager_->RenderTitleScreen();

		// 2. 키 입력 받기 (화면에 글자가 찍히지 않고 키값만 받음)
		int input = _getch();

		// 3. 입력값 검사
		if (input == '1')
		{
			// 게임 시작 (반복문 탈출 -> Run 함수의 다음 단계로 진행)
			break;
		}
		else if (input == '2')
		{
			// 게임 종료 (프로그램 강제 종료)
			// UIManager 정리 등이 필요하다면 여기서 처리하거나,
			// exit(0)은 즉시 꺼지므로 가장 확실한 방법입니다.
			exit(0);
		}

		// 1, 2번 이외의 키(예: 스페이스바, 엔터, a 등)를 누르면
		// 아무 일도 일어나지 않고 while문의 처음으로 돌아가서 다시 입력을 기다림
	}
}

void GameManager::PlayerInputLogic()
{
	// TORO: 기존 입력시스템 주석처리
	/* 
	do {
		Logger::Add(LogType::INFO, "이름을 입력해주세요 : ");
		Console::Input(name_);
	} while (Character::IsValidName(name_) == false);
	*/
	//============================

	// TODO: 입력시스템 수정
	std::string errorMsg = ""; // 에러 메시지를 저장할 변수

	while (true)
	{
		// 1. 캐릭터 생성 화면 출력 (화면을 지우고 다시 그림)
		uiManager_->RenderCharacterCreate();

		// 2. 에러 메시지가 있다면 입력창 위에 빨간색으로 출력
		if (!errorMsg.empty())
		{
			// 입력창(38)보다 94, 48)에 출력
			uiManager_->GotoXY(94, 48);
			std::cout << "\033[31m[오류] " << errorMsg << "\033[0m"; // 빨간색 ANSI 코드
		}

		// 3. 입력 받기 (좌표 94, 50)
		name_ = uiManager_->InputString("이름을 입력해주세요 ", 94, 50);

		// ====================================================
		// [직접 유효성 검사]
		// Character::IsValidName을 쓰면 로그가 출력되므로,
		// 여기서 직접 검사하여 로그 대신 화면에 메시지만 띄웁니다.
		// ====================================================

		// (1) 빈 값 체크
		if (name_.empty())
		{
			errorMsg = "이름이 비어있습니다.";
			continue;
		}

		// (2) 길이 체크 (한글 고려 넉넉하게)
		if (name_.length() > 24)
		{
			errorMsg = "이름이 너무 깁니다. (12자 이내 권장)";
			continue;
		}

		// (3) 공백 체크
		bool hasSpace = false;
		for (char c : name_)
		{
			if (std::isspace(static_cast<unsigned char>(c)))
			{
				hasSpace = true;
				break;
			}
		}

		if (hasSpace)
		{
			errorMsg = "공백은 사용할 수 없습니다.";
			continue;
		}

		// 모든 검사 통과!
		break;
	}

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
	std::string nickname = "참가한 학생 이름: " + player_->GetName();
	Logger::Add(LogType::INFO, nickname);
}

void GameManager::PlayerStatus()
{
	// TORO: 기존 ui 시스템 주석처리
	/*
	Logger::Add(LogType::INFO,
		"이름: " + player_->GetName() +
		" | 정신력: " + std::to_string(player_->GetStatComponent()->GetHp()) + "/" + std::to_string(player_->GetStatComponent()->GetMaxHp()) +
		" | 경험치: " + std::to_string(player_->GetStatComponent()->GetExp()) +
		" | 코딩력: " + std::to_string(player_->GetStatComponent()->GetAttack()) +
		" | 레벨: " + std::to_string(player_->GetStatComponent()->GetLevel()) +
		" | 보유 포인트: " + std::to_string(player_->GetStatComponent()->GetGold()) + " Point"
	);
	*/
	// ============================

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

	// TODO [UI] 전투 메뉴창 잠금 (UI매니저로 전투중 텍스트 출력)
	uiManager_->RenderBattleMode();

	// TODO: 히든 보스 여부 체크
	bool isSpecialBoss = false;

	// TODO: [UI] 몬스터 이미지 출력
	if (curMons_ != nullptr)
	{
		std::string path = curMons_->GetImagePath();

		// [핵심] 파일 이름이 "boss_hoyoung.txt"이면 히든 보스로 판정
		if (path == "boss_hoyoung.txt")
		{
			isSpecialBoss = true;
		}

		// isSpecialBoss가 true면 왼쪽부터 꽉 차게, false면 오른쪽 박스에만 그림
		uiManager_->RenderMonsterArt(path, isSpecialBoss);
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
			curMons_->PlayerKillText();
			break;
		}
	}

	// TODO: [UI] 전투 종료 처리 (히든보스 아닐경우 몬스터 정보창 지우기)
	if (isSpecialBoss == false)
	{
		uiManager_->RenderMonsterArt("empty.txt", false);
	}


	if (!(player_->IsDead()))
	{

		if (player_->GetLv() == 10)
		{
			Logger::Add(LogType::INFO, "훌륭하게 수료하였습니다!");
			Logger::Add(LogType::INFO, "시간을 되돌려 다시 시작하시겠습니까? 예: 1, 아니요: 2");


			// TODO : 입력예외 사용
			int input = SafeInput(uiManager_, "선택: ", 1, 2);

			switch (input)
			{
			case 1:
				return BattleResult::GameClear;
			case 2:
				return BattleResult::ExitGame;
			default:
				Logger::Add(LogType::WARNING, "메인으로 돌아갑니다.");
				return BattleResult::GameClear;
			}

		}

		Logger::Add(LogType::INFO, "과제를 모두 완료했습니다! 보상을 받으세요! ");
		GiveReward();

		// TODO: [UI] 보상 후(골드/경험치) 스탯 갱신
		UpdateDisplay();

		return BattleResult::PlayerWin;
	}
	else
	{
		Logger::Add(LogType::INFO, "정신이 붕괴했습니다. 기억을 잃고 처음으로 돌아갑니다.");
		
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
	Logger::Add(LogType::INFO, "보유 포인트: " + std::to_string(currentGold) + " Point");

	// 아이템 정보
	Inventory* inventory = player_->GetInventory();
	int itemCount = inventory->GetItemCount();

	// TODO: [UI] 메인 패널에 인벤토리 목록 출력
	std::vector<std::string> invList;
	invList.push_back("[ 인벤토리 ]");
	invList.push_back(" ");

	if (itemCount == 0)
	{
		invList.push_back(" ");
		invList.push_back("   [ 가방이 비어있습니다 ]");
		invList.push_back(" ");
	}
	else
	{
		for (int i = 0; i < itemCount; ++i)
		{
			// TODO: 기존 인벤토리 주석처리
			// std::string itemName = inventory->GetItemName(i);
			// Logger::Add(std::to_string(i + 1) + ". " + itemName);

			// TODO: [UI] 아이템 목록 만들기
			// [수정] 널 포인터 체크 (삭제된 아이템 공간 처리)
			if (inventory->GetItem(i) != nullptr)
			{
				invList.push_back(std::to_string(i + 1) + ". " + inventory->GetItemName(i));
			}
			else
			{
				invList.push_back(std::to_string(i + 1) + ". [ 비어있음 ]");
			}
		}
	}

	// TODO: [UI] 
	invList.push_back(" ");
	invList.push_back("0. 돌아가기");

	// TODO: [UI] 
	uiManager_->RenderMainPanel(" INVENTORY ", invList);   // 메인 화면 중앙에 출력
	uiManager_->InputString("0을 눌러 돌아가세요: "); // 키 입력 대기 (확인용)
}

