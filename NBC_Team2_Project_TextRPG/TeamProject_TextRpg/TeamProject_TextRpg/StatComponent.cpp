#include "StatComponent.h"
#include "Logger.h" // 우리가 만든 로거 사용

void StatInfo::ShowInfo()
{
    // 깔끔한 출력을 위해 줄 바꿈
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  [ 캐릭터 정보 : " << name << " ]" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // 레벨과 경험치 (현재 / 목표)
    std::cout << "  Lv. " << level << "\t\t( EXP: " << exp << " / " << maxExp << " )" << std::endl;

    // 체력 (현재 / 최대)
    std::cout << "  HP  : " << hp << " / " << maxHp << std::endl;

    // 공격력
    std::cout << "  ATK : " << attack << std::endl;

    // 골드 (숫자 뒤에 G 붙이기)
    std::cout << "  GOLD: " << gold << " G" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
}

void StatInfo::AddExp(int amount)
{
    exp += amount;
    // 로그에 기록 (디버깅용)
    Logger::Print(INFO, name + "(이)가 경험치를 " + std::to_string(amount) + " 얻었습니다.");

    // 레벨업 루프 (한 번에 경험치를 많이 먹었을 경우 대비)
    while (exp >= maxExp)
    {
        exp -= maxExp; // 경험치 통 비우기 (남은 경험치는 이월)
        level++;       // 레벨 상승

        // 레벨업 보상 (체력 회복 + 스탯 상승)
        maxHp += 20;   // 최대 체력 증가
        hp = maxHp;    // 체력 완전 회복
        attack += 3;   // 공격력 증가
        maxExp += 50;  // 다음 경험치 통은 더 커짐

        // 중요: 레벨업은 중요한 사건이므로 '전투(COMBAT)' 타입 로그나 별도 강조 사용
        Logger::Print(COMBAT, "====== [ 레벨 업! (" + std::to_string(level) + ") ] ======");
    }
}

void StatInfo::AddGold(int amount)
{
    gold += amount;
    Logger::Print(INFO, std::to_string(amount) + " G를 획득했습니다. (현재: " + std::to_string(gold) + " G)");
}