/*
===========================================================================
 [ 스탯 컴포넌트(StatComponent) 사용 가이드 ]

    사용 예시
    [값 읽기]
    int myHp = player.stats.GetHp();      // (O)

    [값 변경]
    player.stats.SetHp(100);              // (O)
    player.stats.SetHp(99999);            // (O) 알아서 MaxHp로 고정됨
    player.stats.SetGold(-500);           // (O) 알아서 0원으로 고정됨

    [정보 출력]
    // 이제 컴포넌트 안에서 cout 하지 않습니다. 문자열만 받아와서 로거에 넘기세요.
    string info = player.stats.GetInfoString(player.name);
    Logger::Add(UI, info);

===========================================================================
*/

#pragma once
#include <string>
#include <iostream>

class StatComponent
{
public:
   
    // 생성자 1. (캐릭터 초기화 담당)
    StatComponent()
        : Hp_(200), MaxHp_(200), Attack_(0),
        Level_(1), Exp_(0), MaxExp_(0), Gold_(0)
    {
        // 생성자 멤버 초기화 
        // HP 200, Attack 30, 레벨 1, 경험치 0, 경험치통 100은 고정값으로 시작합니다.
    }

    //==========================================
    // 생성자 2. (몬스터 오버로딩 초기화 - 취소)
    /*
    StatComponent(int hp, int atk, int exp, int gold)
        : Hp_(hp), MaxHp_(hp), Attack_(atk), // 받은 값으로 초기화
        Level_(1), Exp_(exp), MaxExp_(100), Gold_(gold)
    {
        // 생성자 멤버 초기화 
        // HP 200, Attack 30, 레벨 1, 경험치 0, 경험치통 100은 고정값으로 시작합니다.
    }
    */
    //==========================================

    // [기능] 스탯 출력 (정보창 그리기)
    void ShowInfo(std::string name);

    // [기능] 경험치 획득 (레벨업 로직 포함)
    void AddExp(int amount, std::string name);

    // [기능] 골드 변경 (획득은 양수, 사용은 음수)
    void AddGold(int amount);

    // [Getter] (읽기 전용) ==========================================
    int GetHp() const { return Hp_; }
    int GetMaxHp() const { return MaxHp_; }
    int GetAttack() const { return Attack_; }
    int GetLevel() const { return Level_; }
    int GetMaxLevel() const { return MaxLevel_; }
    int GetExp() const { return Exp_; }
    int GetGold() const { return Gold_; }

    // [Setter] (쓰기 전용) ==========================================
    void SetHp(int hp);
    void SetMaxHp(int maxHp);
    void SetAttack(int attack);
    void SetLevel(int level);
    void SetMaxLevel(int level);
    void SetExp(int exp);
    void SetMaxExp(int maxExp);
    void SetGold(int gold);

private:
    // [1] 기본 정보
    // 이름 - 제외됨. 캐릭터에서 관리함.

    // [2] 전투 스탯
    int Hp_;           // 현재 체력
    int MaxHp_;        // 최대 체력
    int Attack_;       // 공격력

    // [3] 성장 및 재화
    int Level_;        // 레벨
    int MaxLevel_;      // 최대레벨
    int Exp_;          // 현재 경험치
    int MaxExp_;       // 다음 레벨까지 필요한 경험치
    int Gold_;         // 보유 골드(포인트)

    int ClampZero(int value); // 세터 음수체크 함수
};