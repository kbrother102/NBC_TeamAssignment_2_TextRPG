#include "MonsterSpawner.h"
#include "Monster.h"
#include "Goblin.h"
#include "Random.h"

Monster* MonsterSpawner::Spawn()
{
	int num;
	std::vector<Monster*> mobs;
	Monster* ChangMin = new ChangMinKong();
	mobs.push_back(ChangMin);

	//랜덤난수생성
	num = Random::GetRandInt(0,1);

	return mobs[num];
}