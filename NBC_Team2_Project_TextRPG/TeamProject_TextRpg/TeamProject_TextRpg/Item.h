#pragma once
#include <string>

class StatComponent;

class Item
{
public:

    virtual ~Item() = default;
    const std::string GetName() const
    { 
        return name_; 
    }
    int GetPrice() const 
    { 
        return price_;
    }

    //아이템 효과(사용)
    virtual bool Use(StatComponent& stats) = 0;

protected:
    Item(const std::string& name, int price) : name_(name), price_(price) {}

private:
    const std::string name_;
    int price_ = 0 ;
};