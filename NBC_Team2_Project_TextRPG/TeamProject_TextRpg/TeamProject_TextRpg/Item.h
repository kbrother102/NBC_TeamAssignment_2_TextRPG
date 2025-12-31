#pragma once
#include <string>

class StatComponent;

class Item
{
public:
    Item(std::string name, int price);
    virtual ~Item() = default;
    std::string GetName() const;
    int GetPrice() const;

    //아이템 효과(사용)
    virtual void Use(StatComponent& stats) = 0;

protected:
    std::string name_;
    int price_;
};