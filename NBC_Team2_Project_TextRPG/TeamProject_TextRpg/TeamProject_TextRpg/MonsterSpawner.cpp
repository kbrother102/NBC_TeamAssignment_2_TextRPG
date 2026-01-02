#include "MonsterSpawner.h"
#include "Monster.h"
#include "Mob1.h"
#include "Mob2.h"
#include "Random.h"

void MonsterSpawner::Spawn(std::vector<Monster*>& box)
{
	Monster* mob1 = new ChangMinKong();
	Monster* mob2 = new BongJaeKong();
	box.push_back(mob1);
	box.push_back(mob2);
}