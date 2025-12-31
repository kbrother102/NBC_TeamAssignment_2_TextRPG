#include "StatComponent.h"
#include "Logger.h"

// 자주 쓰는 것들 선언 (이제 아래에서 std:: 안 써도 됨)
using std::cout;
using std::endl;
using std::string;
using std::to_string; // 숫자를 스트링 타입으로

// [Private Helper] 입력값 음수 체크 ==================
int StatComponent::ClampZero(int value)
{
    if (value < 0) return 0;
    return value;
}

// [Setter] ==========================================
void StatComponent::SetHp(int hp)
{
    // 1. 음수 검사
    int validHp = ClampZero(hp);

    // 2. 최대 체력 넘는지 검사
    if (validHp > MaxHp_)
    {
        Hp_ = MaxHp_;
    }
    else
    {
        Hp_ = validHp;
    }
}

void StatComponent::SetMaxHp(int maxHp)
{
    // 최대 체력은 최소 1이어야 함
    if (maxHp < 1) maxHp = 1; 
    MaxHp_ = maxHp;

    // 최대 체력이 줄어들었을 때, 현재 체력도 같이 줄여줌 (비율 맞춤)
    if (Hp_ > MaxHp_) Hp_ = MaxHp_;
}

void StatComponent::SetAttack(int attack)
{
    // 음수체크
    Attack_ = ClampZero(attack);
}

void StatComponent::SetLevel(int level)
{
    // 레벨은 최소 1
    if (level < 1) level = 1;
    Level_ = level;
}

void StatComponent::SetExp(int exp)
{
    // 음수체크
    Exp_ = ClampZero(exp);
}

void StatComponent::SetMaxExp(int maxExp)
{
    // 음수체크
    MaxExp_ = ClampZero(maxExp);
}

void StatComponent::SetGold(int gold)
{
    // 음수체크
    Gold_ = ClampZero(gold);
}

//==========================================================
// [수정] 이름을 외부에서 받아오도록 파라미터(string name) 추가
void StatComponent::ShowInfo(string name)
{
    string info = "";

    // 문자열 조립
    info += "\n";
    info += "========================================\n";
    info += "  [ 캐릭터 정보 : " + name + " ]\n";
    info += "----------------------------------------\n";
    info += "  Lv. " + to_string(Level_) + "\t\t( EXP: " + to_string(Exp_) + " / " + to_string(MaxExp_) + " )\n";
    info += "  HP  : " + to_string(Hp_) + " / " + to_string(MaxHp_) + "\n";
    info += "  ATK : " + to_string(Attack_) + "\n";
    info += "  GOLD: " + to_string(Gold_) + " G\n";
    info += "========================================\n";

    // "UI 타입으로 출력"
    Logger::Add(UI, info);
}

// [수정] 경험치 획득 시 '누가' 먹었는지 알기 위해 name 받음
void StatComponent::AddExp(int amount, string name)
{
    Exp_ += amount;

    // 로그 기록: 받아온 name 사용
    Logger::Add(INFO, name + "(이)가 경험치를 " + to_string(amount) + " 얻었습니다.");

    // 레벨업 루프
    while (Exp_ >= MaxExp_)
    {
        Exp_ -= MaxExp_;
        Level_++;

        // 레벨업 보상
        MaxHp_ += 20;
        Hp_ = MaxHp_;
        Attack_ += 3;
        MaxExp_ += 50;

        // 레벨업 축하 로그 (name 사용)
        Logger::Add(COMBAT, "====== [ " + name + " 레벨 업! (" + to_string(Level_) + ") ] ======");
    }
}

// [유지] 골드는 굳이 이름 없어도 되면 그대로 둠 (필요하면 여기도 name 추가 가능)
void StatComponent::AddGold(int amount)
{
    Gold_ += amount;
    Logger::Add(INFO, to_string(amount) + " G를 획득했습니다. (현재: " + to_string(Gold_) + " G)");
}