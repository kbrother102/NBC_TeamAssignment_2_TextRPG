#pragma once
#include <algorithm> 

class StatComponent
{
private:
    int _maxHp;
    int _curHp;
    int _attack;
    int _defense;

public:
    StatComponent(int maxHp, int atk, int def){}
    
    // 상태 확인용 Getter
    int GetCurHp() const { return _curHp; }
    int GetMaxHp() const { return _maxHp; }
    int GetAtk() const { return _attack; }
    bool IsDead() const { return _curHp <= 0; }
};

