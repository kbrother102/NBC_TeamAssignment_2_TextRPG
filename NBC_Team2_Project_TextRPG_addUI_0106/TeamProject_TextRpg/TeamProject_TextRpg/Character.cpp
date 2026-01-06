#include "Character.h"
#include "Inventory.h"
#include "StatComponent.h"
#include "Action.h"
#include "Logger.h"
#include <memory>
#include <cctype>
#include <cassert>

std::string Character::GetType()
{
	return std::string();
}

//생성자
std::unique_ptr<Character> Character::Create(const std::string& name)
{
	//즉시 이름 유효성 판정
	if (!IsValidName(name))
	{
		return nullptr;
	}
	return std::make_unique<Character>(name);
}
//캐릭터는 이름/스텟(컴포넌트의)/인벤토리/액션을 상속받음
Character::Character(const std::string& name)
	: CharacterName_(name),
	stats_(std::make_unique<StatComponent>()),   // 기본 생성자 → 1레벨 스탯
	inventory_(std::make_unique<Inventory>()),
	action_(std::make_unique<Action>(this)) //*this로 넘기기 위해 참조로 바꾸는 것이 누수방지등에 유리함
{	//1레벨 스텟으로 초기화
	StartCharacterStat(1);
}

//레벨(1/10) 경험치(0/100) 체력(200/200) 공격력(30) 골드(0) 으로 설정함수
void Character::StartCharacterStat(int Level)
{	//스텟 초기값 재초기화
	stats_->SetLevel(Level);
	stats_->SetMaxLevel(10);
	stats_->SetExp(0);
	stats_->SetMaxExp(100);
	stats_->SetHp(200);
	stats_->SetMaxHp(200);
	stats_->SetAttack(30);
	stats_->SetGold(0);
}


//캐릭터명 유효성 판정
bool Character::IsValidName(const std::string& name)
{	//비어있으면 실격
	if (name.empty())
	{
		Logger::Add(LogType::WARNING, "이름을 입력해 주세요.");
		return false;
	}
	//16자 미만 제한 -> 24바이트 미만으로 수정
	if (name.length() > 24)
	{
		Logger::Add(LogType::WARNING, "이름이 너무 깁니다.");
		return false;
	}
	//빈 공간이 있으면 실격
	for (char c : name) {
		if (std::isspace(static_cast<unsigned char>(c)))
		{
			Logger::Add(LogType::WARNING, "공백은 사용할 수 없습니다.");
			return false;
		}
	}
	return true;
}

StatComponent* Character::GetStatComponent()
{
	return stats_.get();
}

Inventory* Character::GetInventory()
{
	return inventory_.get();
}

const Inventory* Character::GetInventory() const
{
	return inventory_.get();
}

//void Character::GainGold(int amount)
//{
//	if (amount <= 0) return; // 이상값 방어
//
//	stats_->GainGold(amount);
//}

//void Character::SpendGold(int amount)
//{
//	return stats_->SpendGold(amount);
//}

void Character::ChangeGold(int amount)
{
	return stats_->ChangeGold(amount);
}

Action* Character::GetAction()
{	//const버전의 GetAction을 const만 제거해서 재활용 하고싶다는 구문
	return const_cast<Action*>	//되돌려지는 const Action*에서 const제거
		(static_cast<const Character*>(this)->GetAction()); //const타입에서 참조
}

const Action* Character::GetAction() const
{	//만약 action_이 nullptr이 되면 빌드 단계에서 확인 가능
	assert(action_);
	return action_.get();
}

void Character::AddExp(int amount)
{
	stats_->AddExp(amount);
}

//void Character::AddGold(int amount)
//{
//	stats_->GainGold(amount);
//}

bool Character::IsMaxLv() const
{	//만약 stats_가 nullptr이 되면 빌드 단게에서 확인 가능
	assert(stats_);
	//Level이 MaxLevel이 넘는지를 반환(오버되면 참)
	return stats_->GetLevel() >= stats_->GetMaxLevel();
}

//캐릭터 공격 함수
int Character::GetAttack() const
{
	return stats_->GetAttack();
}

//캐릭터 피격 함수
void Character::TakeDamage(int dmg)
{
	stats_->SetHp(stats_->GetHp() - dmg);
}



//캐릭터의 아이템 사용 함수
bool Character::UseItem(int index)
{
	return inventory_->UseItem(index, *stats_);
}

//캐릭터 사망 판정
bool Character::IsDead() const
{
	return stats_->GetHp() <= 0;
}

int Character::GetHp() const { return stats_->GetHp(); }
int Character::GetMaxHp() const { return stats_->GetMaxHp(); }
int Character::GetAtk() const { return stats_->GetAttack(); }
int Character::GetLv() const { return stats_->GetLevel(); }
int Character::GetExp() const { return stats_->GetExp(); }

//TODO : max exp 추가
int Character::GetMaxExp() const { return stats_->GetMaxExp(); }

int Character::GetGold() const { return stats_->GetGold(); }
std::string Character::GetName() const { return CharacterName_; }