#include "MonsterSpawner.h"
#include "Monster.h"
#include "BasicMob.h"
#include "Random.h"
#include "GameManager.h"

Monster* MonsterSpawner::Spawn()
{
	Monster* mob = new BasicMob();
	return mob;
}