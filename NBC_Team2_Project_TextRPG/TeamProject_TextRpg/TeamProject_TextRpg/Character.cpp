#include "Character.h"
#include "Inventory.h"
#include "StatComponent.h"
#include <memory>
#include <cctype>
//생성자
std::unique_ptr<Character> Character::Create(const std::string& name) //캐릭터는 이름/스텟(컴포넌트의)/인벤토리 를 상속받음
{
	//즉시 이름 유효성 판정
	if (!IsValidName(name))
	{
		return nullptr;
	}
	return std::make_unique<Character>(name);

}
Character::Character(const std::string& name)
	: CharacterName_(name),
	stats_(std::make_unique<StatComponent>()),   // 기본 생성자 → 1레벨 스탯
	inventory_(std::make_unique<Inventory>())
{
}

//캐릭터명 유효성 판정
bool Character::IsValidName(const std::string& name)
{	//비어있으면 실격
	if (name.empty()) return false;
	//16자 미만 제한
	if (name.length() > 16) return false;
	//빈 공간이 있으면 실격
	for (char c : name) {
		if (isspace(c)) return false;
	}
	return true;
}
////캐릭터 경험치 획득 //stat에서 매개변수 수정시 주석 해제
//bool Character::GainExp(int exp)
//{
//	return stats_->AddExp(exp);
//}
////맥스 레벨 함수가 들어오면 주석해제
////캐릭터 최고 레벨 판정
//bool Character::IsMaxLv() const
//{
//	return stats_->GetMaxLevel();
//}


/*
//캐릭터 공격 함수
int Character::Attack()
{
	return stats_->GetAttack();
}
*/
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
int Character::GetGold() const { return stats_->GetGold(); }
const std::string Character::GetName() const { return CharacterName_; }

/*
//전투 완료시 경험치 획득 호출 역할은 스텟 컴포넌트로 이전
bool Character::GainExp(int exp)
{	//최고 레벨 판정 함수 추가예정
	bool reachMaxLv = false;
	//경험치 획득
	Exp_ += exp;
	//레벨업 체크
	while (Exp_ >= 100 && Lv_ < MaxLv_)
	{
		Exp_ -= 100;
		Lv_++;
		MaxHp_ += Lv_ * 20;
		Atk_ += Lv_ * 5;
		Hp_ = MaxHp_;

		if (Lv_ == MaxLv_)
		{
			reachMaxLv = true;
		}
	}
	return IsMaxLv;
}
*/