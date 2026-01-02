#pragma once
#include <string>

class StatComponent;
class Creature
{
protected:
    
public:
    virtual ~Creature() {};
    virtual std::string GetType()=0;
    //타입: Monster, Player (일단기본)
    virtual std::string GetName() const = 0;
    virtual void TakeDamage(int dmg) = 0;
    virtual StatComponent* GetStatComponent() = 0;
};

