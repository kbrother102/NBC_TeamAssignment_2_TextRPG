#include "Console.h"
#include <iostream>
void Console::Input(int& outValue)
{
    std::cin >> outValue;
    ClearBuffer();

}

void Console::Input(std::string& outValue)
{
    std::cin >> outValue;
    ClearBuffer();
}

void Console::ClearBuffer()
{
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    else {
        std::cin.ignore(10000, '\n');
    }
}
