#pragma once
#include<string>
class Console
{
public:
   static void Input(int& outValue);
   static void Input(std::string& outValue);

private:
    static void ClearBuffer();

};

