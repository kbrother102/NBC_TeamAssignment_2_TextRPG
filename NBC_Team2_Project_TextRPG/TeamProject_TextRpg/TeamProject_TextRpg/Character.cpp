#include "Character.h"
#include <iostream>
/* //stats_ 때문에 변경 시 주석 해제 예정
//생성자
Character::Character(const std::string& name) : CharacterName_(name), stats_(), inventory_()
{	//즉시 이름 유효성 판정
	if (!IsValidName(name))
	{	//임시 반환명 생성
		CharacterName_ = "이름이 없습니다.";
		return;
	}

}
*/
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
//전투 완료시 경험치 획득 호출
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
// 마찬가지 생성자 체크가 될 때 해제할 것
////캐릭터 공격 함수
//int Character::Attack()
//{
//	int damage = StatComponent_.calculateAttack();
//	/* //20퍼센트 확률 치명타(2배 데미지)
//	if(rand()% 100<20)
//	{
//		damage *= 2;
//	}
//	*/
//	return damage;
//}

//캐릭터 피격 함수
void Character::TakeDamage(int dmg)
{
	Hp_ -= dmg;
	if (Hp_ < 0)
		Hp_ = 0;
}
//캐릭터 사망 판정
bool Character::IsDead() const
{
	return Hp_ <= 0;
}
//캐릭터 최고 레벨 판정
bool Character::IsMaxLv() const
{
	return Lv_ >= 10;
}
//캐릭터의 아이템 사용 함수
//bool Character::UseItem(int index)
//{
//	return inventory_.UseItem(index, stats_);
//}