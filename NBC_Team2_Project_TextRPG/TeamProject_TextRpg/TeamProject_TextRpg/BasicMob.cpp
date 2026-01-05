#include "BasicMob.h"
#include "Logger.h"
#include "Random.h"

void BasicMob::SpawnMob(int Level)
{
	//mobNum_ = Random::GetRandInt(0, 6);
	mobNum_ = 6;
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
				Logger::Add(LogType::INFO, "보스몬스터 : " + GetName() +
					"출현! 목표코딩력 : " + std::to_string(monStat_->GetHp()) + " 과제량 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::TALK, "아...아... 제 목소리 잘 들리시나요??");
			}
			else
			{
				mobNum_ = 0;
				SetStat(Level);
				name_ = "포인터 강의해주시는 승현튜터님";
				Logger::Add(LogType::INFO, "일반몬스터 : " + GetName() +
					"출현! 목표코딩력 : " + std::to_string(monStat_->GetHp()) + " 과제량 : " + std::to_string(monStat_->GetAttack()));
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
				Logger::Add(LogType::INFO, "보스몬스터 : " + GetName() +
					"출현! 목표코딩력 : " + std::to_string(monStat_->GetHp()) + " 과제량 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::TALK, "이 코드가 이게 최선일까요?? 한번 더 생각해보셨나요??");
			}
			else
			{
				mobNum_ = 1;
				SetStat(Level);
				name_ = "튜터링 해주시는 극민튜터님";
				Logger::Add(LogType::INFO, "일반몬스터 : " + GetName() +
					"출현! 목표코딩력 : " + std::to_string(monStat_->GetHp()) + " 과제량 : " + std::to_string(monStat_->GetAttack()));
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
				Logger::Add(LogType::INFO, "보스몬스터 : " + GetName() +
					"출현! 목표코딩력 : " + std::to_string(monStat_->GetHp()) + " 과제량 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::TALK, "저는 여러분들께 아무런 기대도 하지 않습니다.");
			}
			else
			{
				mobNum_ = 2;
				SetStat(Level);
				name_ = "공룡을 탄 은일튜터님";
				Logger::Add(LogType::INFO, "일반몬스터 : " + GetName() +
					"출현! 목표코딩력 : " + std::to_string(monStat_->GetHp()) + " 과제량 : " + std::to_string(monStat_->GetAttack()));
			}
			break;
		case TuterName::CHANGMINKONG:
			if (Level > 9)
			{
				mobNum_ = 3;
				SetStatBoss(Level);
				name_ = "카페인충전한 창민튜터님";
				bIsBoss_ = true;
				bUseSkill_ = false;
				Logger::Add(LogType::INFO, "보스몬스터 : " + GetName() +
					"출현! 목표코딩력 : " + std::to_string(monStat_->GetHp()) + " 과제량 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::TALK, "여러분들의 성장을 위해서라면 카페인충전도 할 수 있습니다!");
			}
			else
			{
				mobNum_ = 3;
				SetStat(Level);
				name_ = "닮은살걀 먹방중인 창민튜터님";
				Logger::Add(LogType::INFO, "일반몬스터 : " + GetName() +
					"출현! 목표코딩력 : " + std::to_string(monStat_->GetHp()) + " 과제량 : " + std::to_string(monStat_->GetAttack()));
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
				Logger::Add(LogType::INFO, "보스몬스터 : " + GetName() +
					"출현! 목표코딩력 : " + std::to_string(monStat_->GetHp()) + " 과제량 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::TALK, "조금 진지해질필요가 있겠네요.");
			}
			else
			{
				mobNum_ = 4;
				SetStat(Level);
				name_ = "모자를 쓴 봉재튜터님";
				Logger::Add(LogType::INFO, "일반몬스터 : " + GetName() +
					"출현! 목표코딩력 : " + std::to_string(monStat_->GetHp()) + " 과제량 : " + std::to_string(monStat_->GetAttack()));
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
				Logger::Add(LogType::INFO, "보스몬스터 : " + GetName() +
					"출현! 목표코딩력 : " + std::to_string(monStat_->GetHp()) + " 과제량 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::TALK, "여러분 우리 혹여나 마주쳐도 아는척하지말아요...");
			}
			else
			{
				mobNum_ = 5;
				SetStat(Level);
				name_ = "가상배경의 조은튜터님";
				Logger::Add(LogType::INFO, "일반몬스터 : " + GetName() +
					"출현! 목표코딩력 : " + std::to_string(monStat_->GetHp()) + " 과제량 : " + std::to_string(monStat_->GetAttack()));
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
				Logger::Add(LogType::WARNING, "특수 보스몬스터 : " + GetName() +
					"출현! 체력 : " + std::to_string(monStat_->GetHp()) + " 물리력 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::WARNING, "여러분들의 정신상태를 고칠 필요가 있겠네요.");
			}
			else
			{
				mobNum_ = 6;
				SetStatHoYoung(Level);
				name_ = "새천년 건강체조를 시작한 호영튜터님";
				Logger::Add(LogType::WARNING, "특수 일반몬스터 : " + GetName() +
					"출현! 체력 : " + std::to_string(monStat_->GetHp()) + " 물리력 : " + std::to_string(monStat_->GetAttack()));
				Logger::Add(LogType::WARNING, "안녕하세요 여러분 조호영튜터입니다.");
			}
			break;
		}
	}
	else
	{
		Logger::Add(LogType::WARNING, "이미 튜터님과 튜터링중입니다 집중하세요!!!!");
		return;
	}
}

void BasicMob::UseSkill()
{
	switch ((TuterName)mobNum_)
	{
	case TuterName::SEUNGHYEONSUN:
		Logger::Add(LogType::INFO, "보스체력 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "마이크를 먹을순 없고 자 이제 잘 들리시죠??");
		monStat_->SetAttack(monStat_->GetAttack() + 10);
		break;
	case TuterName::GEUKMINKONG:
		Logger::Add(LogType::INFO, "보스체력 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "난이도를 좀 더 올려도 되겠어요!");
		monStat_->SetAttack(monStat_->GetAttack() + 15);
		break;
	case TuterName::EUNILPERK:
		Logger::Add(LogType::INFO, "보스체력 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "안되는건 없습니다 여러분들은 할 수 있습니다.");
		monStat_->SetAttack(monStat_->GetAttack() + 15);
		break;
	case TuterName::CHANGMINKONG:
		Logger::Add(LogType::INFO, "보스체력 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "잠시 배가고파서 삶은달걀 먹방을 좀 하겠습니다.");
		monStat_->SetHp(monStat_->GetHp() + 100);
		break;
	case TuterName::BONGJAEKONG:
		Logger::Add(LogType::INFO, "보스체력 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "여러분들이 문제를 잘 풀어주시는거같아서 좀 더 많은 문제를 준비했습니다!");
		monStat_->SetHp(monStat_->GetHp() + 50);
		break;
	case TuterName::JOEUNKONG:
		Logger::Add(LogType::INFO, "보스체력 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "미니실습이랑 도전실습이 쉬우시다구요? 그렇다면 도전x도전 실습도 한번 도전해봅시다!");
		monStat_->SetHp(monStat_->GetHp() + 50);
		monStat_->SetAttack(monStat_->GetAttack() + 10);
		break;
	case TuterName::HOYOUNGJOU:
		Logger::Add(LogType::INFO, "보스체력 절반이하! 스킬발동!");
		Logger::Add(LogType::TALK, "코딩할때도 체력이중요합니다!!! 체력!!! 운동하십쇼!!!!");
		monStat_->SetHp(monStat_->GetHp() + 200);
		monStat_->SetAttack(monStat_->GetAttack() + 20);
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

void BasicMob::GetDie()
{
	switch ((TuterName)mobNum_)
	{
	case TuterName::SEUNGHYEONSUN:
		Logger::Add(LogType::TALK, "항상 그림을 그려서 코딩하시면 쉽게 접근하실수 있습니다 잊지마세요!");
		break;
	case TuterName::GEUKMINKONG:
		Logger::Add(LogType::TALK, "잘하셨습니다! 여러분들 무사히 수료하시길 기원하겠습니다!");
		break;
	case TuterName::EUNILPERK:
		Logger::Add(LogType::TALK, "이제 여러분들께 기대를 해도 될거같아서 뿌듯하네요.");
		break;
	case TuterName::CHANGMINKONG:
		Logger::Add(LogType::TALK, "좋습니다 여러분 그상태로 계속 가시면 됩니다!");
		break;
	case TuterName::BONGJAEKONG:
		Logger::Add(LogType::TALK, "역시 여러분들은 해내실줄 알았습니다.");
		break;
	case TuterName::JOEUNKONG:
		Logger::Add(LogType::TALK, "너무 잘하셔서 더이상 가르칠게 없을거같아요 나이스!");
		break;
	case TuterName::HOYOUNGJOU:
		Logger::Add(LogType::TALK, "같이 새천년 건강체조 하러 갑시다!!");
		break;
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
		GetDie();
	}
	else return;
}