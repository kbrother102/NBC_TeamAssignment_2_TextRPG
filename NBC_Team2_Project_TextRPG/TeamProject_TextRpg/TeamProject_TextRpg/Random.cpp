#include "Random.h"
#include <random>

//min~max 까지 정수
int Random::GetRandInt(int min, int max)
{

    std::uniform_int_distribution<int> dist(min, max);
    return dist(GetRandomEngine());
}
//사용법 Random::GetRandInt(최솟값, 최댓값);

// 0.0f ~ 1.0f 사이 실수
float Random::GetRandFloat()
{

    
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    return dist(GetRandomEngine());
}
//사용법 Random::GetRandfloat();
std::mt19937& Random::GetRandomEngine()
{
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
    
}
