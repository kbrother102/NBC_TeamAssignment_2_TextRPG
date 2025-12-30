#pragma once
#include <string>
class Item
{
    virtual std::string GetName() =0 ;
    virtual void Use(class Character* character) = 0;
};

