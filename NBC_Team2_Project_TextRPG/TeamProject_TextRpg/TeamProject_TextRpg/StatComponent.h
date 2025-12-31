#pragma once
#include <string>
#include <iostream>

class StatInfo
{
public:
    // [1] 기본 정보
    std::string name; // 이름

    // [2] 전투 스탯
    int hp;           // 현재 체력
    int maxHp;        // 최대 체력
    int attack;       // 공격력

    // [3] 성장 및 재화
    int level;        // 레벨
    int exp;          // 현재 경험치
    int maxExp;       // 다음 레벨까지 필요한 경험치
    int gold;         // 보유 골드

    // 생성자 (초기화 담당)
    StatInfo(std::string _name, int _hp, int _atk, int _def, int _gold = 0)
        : name(_name), hp(_hp), maxHp(_hp), attack(_atk),
        level(1), exp(0), maxExp(100), gold(_gold)
    {
        // 생성자는 멤버 초기화 리스트(:)를 쓰는 게 성능에 더 좋습니다.
        // 레벨 1, 경험치 0, 경험치통 100은 고정값으로 시작합니다.
    }

    // [기능] 스탯 출력 (정보창 그리기)
    void ShowInfo();

    // [기능] 경험치 획득 (레벨업 로직 포함)
    void AddExp(int amount);

    // [기능] 골드 변경 (획득은 양수, 사용은 음수)
    void AddGold(int amount);
};