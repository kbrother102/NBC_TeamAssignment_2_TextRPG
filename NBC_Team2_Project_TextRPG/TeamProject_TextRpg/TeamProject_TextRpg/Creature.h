#pragma once
#include <string>
class Creature
{
protected:
    std::string Type_;
public:
    virtual ~Creature() {};
    //타입: Monster, Player (일단기본)
    virtual std::string GetType() = 0 ;
};

