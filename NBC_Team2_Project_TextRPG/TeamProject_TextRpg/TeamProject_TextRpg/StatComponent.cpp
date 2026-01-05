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
void StatComponent::SetIsDead(bool bIsDead)
{
    // [예외처리 1] 중복 상태 방지
    // 이미 죽어있는데 또 죽인다고 하거나, 살아있는데 또 살리는 경우 무시
    if (bIsDead_ == bIsDead)
    {
        return;
    }

    bIsDead_ = bIsDead;

    // [예외처리 2] 상태와 HP의 동기화 (좀비/유령 현상 방지)
    if (bIsDead_)
    {
        // 죽음 상태로 만들 때, HP가 남아있다면 0으로 처리
        if (Hp_ > 0)
        {
            Hp_ = 0;
            // 필요하다면 여기서 사망 로그 출력이나 델리게이트 호출
            // std::cout << " -> HP 강제 조정됨: 사망 상태 확인" << std::endl;
        }
    }
    else
    {
        // 부활(false) 시켰는데 HP가 0 이하라면? 바로 다시 죽어버림.
        // 최소한의 생명력(1)을 부여하거나 경고를 띄움
        if (Hp_ <= 0)
        {
            Hp_ = 1;
            Logger::Add(LogType::WARNING, "HP가 0인 상태에서 부활했습니다. HP를 1로 조정합니다.");
        }
    }
}


void StatComponent::SetType(string type)
{
    // [최적화] 함수가 불릴 때마다 벡터를 새로 만들지 않도록 static const 사용
    // 예외처리용 "Normal" 타입 추가
    static const std::vector<string> allowedTypes = { "Normal", "Player", "Monster", "Boss", "SpacialMob", "SpacialBoss"};

    // [예외처리 1] 빈 문자열 입력 방지
    if (type.empty())
    {
        // Logger가 있다면 사용, 없다면 오류 로그 출력
        Logger::Add(LogType::WARNING, "타입 이름이 비어있습니다. 기본값(Normal)으로 설정합니다.");
        
        // 빈 값이면 '일반'으로 강제 설정
        Type_ = "Normal";
        return;
    }

    // [예외처리 2] 허용된 타입인지 검사 (화이트리스트)
    auto it = std::find(allowedTypes.begin(), allowedTypes.end(), type);
    if (it == allowedTypes.end())
    {
        // 오타 발생 시 (예: "Bose")
        Logger::Add(LogType::WARNING, "정의되지 않은 타입 이름입니다." + type + "->'Normal'로 대체합니다.");

        Type_ = "Normal";
        return;
    }

    // 통과 시 적용
    Type_ = type;
}

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

void StatComponent::SetMaxLevel(int maxlevel)
{
    // 레벨은 최소 1
    if (maxlevel < 1) maxlevel = 1;
    MaxLevel_ = maxlevel;
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

// [수정] string name 삭제
void StatComponent::AddExp(int amount)
{
    Exp_ += amount;

    // 로그 기록: 받아온 name 사용
    Logger::Add(INFO, "플레이어가 경험치를 " + to_string(amount) + " 얻었습니다.");

    // 레벨업 루프
    while (Exp_ >= MaxExp_)
    {
        Exp_ -= MaxExp_;
        Level_++;

        // 레벨업 보상
        MaxHp_ += Level_ * 20;
        Hp_ = MaxHp_;
        Attack_ += Level_ * 5;

        // 레벨업 축하 로그 (name 사용)
        Logger::Add(COMBAT, "====== [ 플레이어 레벨 업! (" + to_string(Level_) + ") ] ======");
    }
}


// [ChangeGold로 통합]
void StatComponent::ChangeGold(int changeamount)
{
    int FinalGold = GetGold() + changeamount;
    SetGold(FinalGold);
}

// [유지] 골드는 굳이 이름 없어도 되면 그대로 둠 (필요하면 여기도 name 추가 가능)
void StatComponent::GainGold(int gainamount)
{
    gainamount = ClampZero(gainamount);
    Gold_ += gainamount;
}

void StatComponent::SpendGold(int spendamount)
{
    if (spendamount > 0) spendamount = 0;
    Gold_ += spendamount;
}
