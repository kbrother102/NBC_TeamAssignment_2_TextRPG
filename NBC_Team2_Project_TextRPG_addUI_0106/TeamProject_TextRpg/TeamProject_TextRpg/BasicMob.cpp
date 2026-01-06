#include "BasicMob.h"
#include "Logger.h"
#include "Random.h"

// TODO 몬스터 이름 (txt 파일 링크용)
const std::string TUTOR_IDS[] = {
	"seunghyeon",
	"geukmin",
	"eunil",
	"changmin",
	"bongjae",
	"joeun",
	"hoyoung"
};


void BasicMob::SpawnMob(int Level)
{
	mobNum_ = Random::GetRandInt(0, 6);
	if ((monStat_->GetIsDead() == true))
	{
		switch ((TuterName)mobNum_)
		{
		case TuterName::SEUNGHYEONSUN:
			if (Level > 9)
			{
				mobNum_ = 0;
				SetStatBoss(Level);
				name_ = "마이크가 불안정한 승현튜터님";
				bIsBoss_ = true;
				bUseSkill_ = false;
				Logger::Add(LogType::INFO, "보스 -" + GetName() +
					"출현! 남은 과제량 : " + std::to_string(monStat_->GetHp()) + " 코드 리뷰 시간 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::TALK, "아...아... 제 목소리 잘 들리시나요??");
			}
			else
			{
				mobNum_ = 0;
				SetStat(Level);
				name_ = "포인터 강의해주시는 승현튜터님";
				Logger::Add(LogType::INFO, "일반 - " + GetName() +
					"출현! 남은 과제량 : " + std::to_string(monStat_->GetHp()) + " 코드 리뷰 시간 : " + std::to_string(monStat_->GetAttack()));
			}
			break;
		case TuterName::GEUKMINKONG:
			if (Level > 9)
			{
				mobNum_ = 1;
				SetStatBoss(Level);
				name_ = "코드리뷰를 시작한 극민튜터님";
				bIsBoss_ = true;
				bUseSkill_ = false;
				Logger::Add(LogType::INFO, "보스 -" + GetName() +
					"출현! 남은 과제량 : " + std::to_string(monStat_->GetHp()) + " 코드 리뷰 시간 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::TALK, "이 코드가 이게 최선일까요?? 한번 더 생각해보셨나요??");
			}
			else
			{
				mobNum_ = 1;
				SetStat(Level);
				name_ = "튜터링 해주시는 극민튜터님";
				Logger::Add(LogType::INFO, "일반 - " + GetName() +
					"출현! 남은 과제량 : " + std::to_string(monStat_->GetHp()) + " 코드 리뷰 시간 : " + std::to_string(monStat_->GetAttack()));
			}
			break;
		case TuterName::EUNILPERK:
			if (Level > 9)
			{
				mobNum_ = 2;
				SetStatBoss(Level);
				name_ = "기대를 안하는 은일튜터님";
				bIsBoss_ = true;
				bUseSkill_ = false;
				Logger::Add(LogType::INFO, "보스 -" + GetName() +
					"출현! 남은 과제량 : " + std::to_string(monStat_->GetHp()) + " 코드 리뷰 시간 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::TALK, "저는 여러분들께 아무런 기대도 하지 않습니다.");
			}
			else
			{
				mobNum_ = 2;
				SetStat(Level);
				name_ = "공룡을 탄 은일튜터님";
				Logger::Add(LogType::INFO, "일반 - " + GetName() +
					"출현! 남은 과제량 : " + std::to_string(monStat_->GetHp()) + " 코드 리뷰 시간 : " + std::to_string(monStat_->GetAttack()));
			}
			break;
		case TuterName::CHANGMINKONG:
			if (Level > 9)
			{
				mobNum_ = 3;
				SetStatBoss(Level);
				name_ = "키부츠지 창민";
				bIsBoss_ = true;
				bUseSkill_ = false;
				Logger::Add(LogType::INFO, "보스 -" + GetName() +
					"출현! 남은 과제량 : " + std::to_string(monStat_->GetHp()) + " 코드 리뷰 시간 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::TALK, "이 아이..왠지모르게 익숙한 냄새가...C++호흡의 냄새가!!");
			}
			else
			{
				mobNum_ = 3;
				SetStat(Level);
				name_ = "(닮은살걀)무언가를 먹방중인 창민튜터님";
				Logger::Add(LogType::INFO, "일반 - " + GetName() +
					"출현! 남은 과제량 : " + std::to_string(monStat_->GetHp()) + " 코드 리뷰 시간 : " + std::to_string(monStat_->GetAttack()));
			}
			break;
		case TuterName::BONGJAEKONG:
			if (Level > 9)
			{
				mobNum_ = 4;
				SetStatBoss(Level);
				name_ = "모자를 벗은 봉재튜터님";
				bIsBoss_ = true;
				bUseSkill_ = false;
				Logger::Add(LogType::INFO, "보스 -" + GetName() +
					"출현! 남은 과제량 : " + std::to_string(monStat_->GetHp()) + " 코드 리뷰 시간 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::TALK, "조금 진지해질필요가 있겠네요.");
			}
			else
			{
				mobNum_ = 4;
				SetStat(Level);
				name_ = "모자를 쓴 봉재튜터님";
				Logger::Add(LogType::INFO, "일반 - " + GetName() +
					"출현! 남은 과제량 : " + std::to_string(monStat_->GetHp()) + " 코드 리뷰 시간 : " + std::to_string(monStat_->GetAttack()));
			}
			break;
		case TuterName::JOEUNKONG:
			if (Level > 9)
			{
				mobNum_ = 5;
				SetStatBoss(Level);
				name_ = "팔당으로 점프하신 조은튜터님";
				bIsBoss_ = true;
				bUseSkill_ = false;
				Logger::Add(LogType::INFO, "보스 -- " + GetName() +
					"출현! 남은 과제량 : " + std::to_string(monStat_->GetHp()) + " 코드 리뷰 시간 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::TALK, "여러분 우리 혹여나 마주쳐도 아는척하지말아요...");
			}
			else
			{
				mobNum_ = 5;
				SetStat(Level);
				name_ = "가상배경의 조은튜터님";
				Logger::Add(LogType::INFO, "일반 - " + GetName() +
					"출현! 남은 과제량 : " + std::to_string(monStat_->GetHp()) + " 코드 리뷰 시간 : " + std::to_string(monStat_->GetAttack()));
			}
			break;

		case TuterName::HOYOUNGJOU:
			if (Level > 9)
			{
				mobNum_ = 6;
				SetStatHoYoungBoss(Level);
				name_ = "풀무장한 호영튜터님";
				bIsBoss_ = true;
				bUseSkill_ = false;
				Logger::Add(LogType::WARNING, "특수 보스 -" + GetName() +
					"출현! 체력 : " + std::to_string(monStat_->GetHp()) + " 물리력 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::WARNING, "여러분들의 정신상태를 고칠 필요가 있겠네요.");
			}
			else
			{
				mobNum_ = 6;
				SetStatHoYoung(Level);
				name_ = "건강체조를 시작한 호영튜터님";
				Logger::Add(LogType::WARNING, "특수 일반 - " + GetName() +
					"출현! 체력 : " + std::to_string(monStat_->GetHp()) + " 물리력 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::WARNING, "안녕하세요 조호영튜터입니다.");
			}
			break;
		}
	}
	else
	{
		Logger::Add(LogType::WARNING, "이미 튜터님과 튜터링중입니다 집중하세요!!!!");
		return;
	}

	// TODO: [UI] 이미지 파일명 자동 생성기 
	// -----------------------------------------------------------
	// 1. 접두사 결정 (보스면 "boss_", 일반이면 "mob_")
	std::string prefix = bIsBoss_ ? "boss_" : "mob_";

	// 2. 튜터 영문 이름 가져오기 (배열 인덱스 활용)
	// 예외: mobNum_이 범위 밖이면 기본값 0번 사용
	int idx = (mobNum_ >= 0 && mobNum_ <= 6) ? mobNum_ : 0;
	std::string id = TUTOR_IDS[idx];

	// 3. 최종 파일명 조립 (예: "boss_seunghyeon.txt")
	std::string finalPath = prefix + id + ".txt";

	// 4. 적용
	SetImagePath(finalPath);


}

void BasicMob::UseSkill()
{
	switch ((TuterName)mobNum_)
	{
	case TuterName::SEUNGHYEONSUN:
		Logger::Add(LogType::INFO, "보스 - 과제량 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "마이크를 먹을순 없고 자 이제 잘 들리시죠??");
		Logger::Add(LogType::INFO, "코드 리뷰 시간 100증가!");
		monStat_->SetAttack(monStat_->GetAttack() + 100);
		break;
	case TuterName::GEUKMINKONG:
		Logger::Add(LogType::INFO, "보스 - 과제량 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "난이도를 좀 더 올려도 되겠어요!");
		Logger::Add(LogType::INFO, "코드 리뷰 시간 150증가!");
		monStat_->SetAttack(monStat_->GetAttack() + 150);
		break;
	case TuterName::EUNILPERK:
		Logger::Add(LogType::INFO, "보스 - 과제량 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "안되는건 없습니다 여러분들은 할 수 있습니다.");
		Logger::Add(LogType::INFO, "코드 리뷰 시간 100증가!");
		monStat_->SetAttack(monStat_->GetAttack() + 100);
		break;
	case TuterName::CHANGMINKONG:
		Logger::Add(LogType::INFO, "보스 - 과제량 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "상현1 창민객체 조창민 소환!");
		Logger::Add(LogType::INFO, "보스 - 과제량 1000 증가!");
		monStat_->SetHp(monStat_->GetHp() + 1000);
		break;
	case TuterName::BONGJAEKONG:
		Logger::Add(LogType::INFO, "보스 - 과제량 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "여러분들이 문제를 잘 풀어주시는거같아서 좀 더 많은 문제를 준비했습니다!");
		Logger::Add(LogType::INFO, "보스 - 과제량 500 증가!");
		monStat_->SetHp(monStat_->GetHp() + 500);
		break;
	case TuterName::JOEUNKONG:
		Logger::Add(LogType::INFO, "보스 - 과제량 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "미니실습이랑 도전실습이 쉬우시다구요? 그렇다면 도전x도전 실습도 한번 도전해봅시다!");
		Logger::Add(LogType::INFO, "보스 - 과제량 300 증가! 코드 리뷰 시간 70 증가!");
		monStat_->SetHp(monStat_->GetHp() + 300);
		monStat_->SetAttack(monStat_->GetAttack() + 70);
		break;
	case TuterName::HOYOUNGJOU:
		Logger::Add(LogType::INFO, "보스 - 과제량 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "천! 리! 행! 군!");
		Logger::Add(LogType::INFO, "보스 - 과제량 두배 증가! 코드 리뷰 시간 절반 감소!");
		monStat_->SetHp(monStat_->GetHp() * 2);
		monStat_->SetAttack(monStat_->GetAttack() / 2);
		break;
	}
}

void BasicMob::SetStat(int Level)
{
	monStat_->SetMaxHp(Level * Random::GetRandInt(20, 30));
	monStat_->SetAttack(Level * Random::GetRandInt(5, 10));
	monStat_->SetHp(monStat_->GetMaxHp());
	monStat_->SetIsDead(false);
	monStat_->SetType("Monster");
	monStat_->SetLevel(Level);
	monStat_->SetExp(50);
	monStat_->SetGold(Random::GetRandInt(10, 20));
}

void BasicMob::SetStatBoss(int Level)
{
	monStat_->SetMaxHp(Level * Random::GetRandInt(60, 90));
	monStat_->SetAttack(Level * Random::GetRandInt(15, 30));
	monStat_->SetHp(monStat_->GetMaxHp());
	monStat_->SetIsDead(false);
	monStat_->SetType("Boss");
	monStat_->SetLevel(Level);
	monStat_->SetExp(2026);
	monStat_->SetGold(2026);
}

void BasicMob::SetStatHoYoung(int Level)
{
	monStat_->SetMaxHp(Level * Random::GetRandInt(40, 60));
	monStat_->SetAttack(Level * Random::GetRandInt(1, 40));
	monStat_->SetHp(monStat_->GetMaxHp());
	monStat_->SetIsDead(false);
	monStat_->SetType("SpacialMob");
	monStat_->SetLevel(Level + 10);
	monStat_->SetExp(250);
	monStat_->SetGold(Random::GetRandInt(50, 100));
}

void BasicMob::SetStatHoYoungBoss(int Level)
{
	monStat_->SetMaxHp(Level * Random::GetRandInt(100, 150));
	monStat_->SetAttack(Level * Random::GetRandInt(1, 100));
	monStat_->SetHp(monStat_->GetMaxHp());
	monStat_->SetIsDead(false);
	monStat_->SetType("SpacialBoss");
	monStat_->SetLevel(Level + 999);
	monStat_->SetExp(9999);
	monStat_->SetGold(9999);
}

void BasicMob::PlayerKillText()
{
	switch ((TuterName)mobNum_)
	{
	case TuterName::SEUNGHYEONSUN:
		Logger::Add(LogType::TALK, "지금 못한다고 너무 좌절하지마세요 처음엔 다 그러는겁니다");
		break;
	case TuterName::GEUKMINKONG:
		Logger::Add(LogType::TALK, "너무 겁먹지마세요 제가 다시 도와드리겠습니다");
		break;
	case TuterName::EUNILPERK:
		Logger::Add(LogType::TALK, "여러분 공부에는 끝이없습니다");
		break;
	case TuterName::CHANGMINKONG:
		Logger::Add(LogType::TALK, "여러분들도 노력해서 창민객체가 될수 있도록 하십쇼! HaHaHa");
		break;
	case TuterName::BONGJAEKONG:
		Logger::Add(LogType::TALK, "정 모르겠으면 GPT에게 도움을 청하는것도 방법입니다");
		break;
	case TuterName::JOEUNKONG:
		Logger::Add(LogType::TALK, "도전x도전 실습은 필수가 아닙니다!");
		break;
	case TuterName::HOYOUNGJOU:
		Logger::Add(LogType::TALK, "제가 블루프린트 노드 정리 깔끔하게 하라고 말씀드렸죠??");
		break;
	}
}

void BasicMob::GetDie()
{
	if (bIsBoss_ == true)
	{
		switch ((TuterName)mobNum_)
		{
		case TuterName::SEUNGHYEONSUN:
			Logger::Add(LogType::TALK, "항상 그림을 그려서 코딩하시면 쉽게 접근하실수 있습니다 잊지마세요!");
			break;
		case TuterName::GEUKMINKONG:
			Logger::Add(LogType::TALK, "이런 코드도 사용하실줄 아시군요 대단합니다!");
			break;
		case TuterName::EUNILPERK:
			Logger::Add(LogType::TALK, "이제 여러분들께 기대를 해도 될거같아서 뿌듯하네요.");
			break;
		case TuterName::CHANGMINKONG:
			Logger::Add(LogType::TALK, "다음번엔 더 강력한 과제를 제출해주마!");
			break;
		case TuterName::BONGJAEKONG:
			Logger::Add(LogType::TALK, "역시 여러분들은 해내실줄 알았습니다.");
			break;
		case TuterName::JOEUNKONG:
			Logger::Add(LogType::TALK, "이제 아는척 해야겠는데요?");
			break;
		case TuterName::HOYOUNGJOU:
			Logger::Add(LogType::TALK, "체력도 충분한거같네요 여러분 같이 헬스하러 가실까요?");
			break;
		}
	}
	else
	{
		switch ((TuterName)mobNum_)
		{
		case TuterName::SEUNGHYEONSUN:
			Logger::Add(LogType::TALK, "항상 그림을 그려서 코딩하시면 쉽게 접근하실수 있습니다 잊지마세요!");
			break;
		case TuterName::GEUKMINKONG:
			Logger::Add(LogType::TALK, "잘하셨습니다! 여러분들은 할수 있어요!! 충분히 잘하고 계십니다!!");
			break;
		case TuterName::EUNILPERK:
			Logger::Add(LogType::TALK, "다들 잘하시는군요 할게 없으면 저한테 오시면 됩니다.");
			break;
		case TuterName::CHANGMINKONG:
			Logger::Add(LogType::TALK, "좋습니다 여러분 그상태로 계속 가시면 됩니다!");
			break;
		case TuterName::BONGJAEKONG:
			Logger::Add(LogType::TALK, "이정도 난이도는 다들 쉬우시군요!");
			break;
		case TuterName::JOEUNKONG:
			Logger::Add(LogType::TALK, "너무 잘하셔서 더이상 가르칠게 없을거같아요 나이스!");
			break;
		case TuterName::HOYOUNGJOU:
			Logger::Add(LogType::TALK, "다들 체력이 좋으시네요");
			break;
		}
	}
	monAct_->Die();
}

void BasicMob::TakeDamage(int dmg)
{
	monStat_->SetHp(monStat_->GetHp() - dmg);
	if ((monStat_->GetHp()) < (monStat_->GetMaxHp() / 2) && bIsBoss_ == true && bUseSkill_ == false)
	{
		UseSkill();
		bUseSkill_ = true;
	}


	if (monStat_->GetHp() <= 0)
	{
		monStat_->SetIsDead(true);
	}
	else return;
}