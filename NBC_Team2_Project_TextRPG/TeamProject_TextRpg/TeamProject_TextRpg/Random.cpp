#include "Random.h"
#include <Random>

//min~max 까지 정수
int Random::GetRandInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// 0.0f ~ 1.0f 사이 실수
float Random::GetRandFloat()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    return dist(gen);
}
