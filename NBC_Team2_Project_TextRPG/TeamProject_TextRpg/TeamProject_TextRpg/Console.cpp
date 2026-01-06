#include "Console.h"
#include <iostream>
void Console::Input(int& outValue)
{
    std::cin >> outValue;
    ClearBuffer();

}

void Console::Input(std::string& outValue)
{
    std::getline(std::cin, outValue);
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
