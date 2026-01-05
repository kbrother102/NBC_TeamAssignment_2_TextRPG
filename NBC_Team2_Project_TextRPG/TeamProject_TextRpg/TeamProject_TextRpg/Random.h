#pragma once
#include<random>


class Random
{
public:
    static int GetRandInt(int min, int max);
    static float GetRandFloat();
private:
    static std::mt19937& GetRandomEngine();
};

