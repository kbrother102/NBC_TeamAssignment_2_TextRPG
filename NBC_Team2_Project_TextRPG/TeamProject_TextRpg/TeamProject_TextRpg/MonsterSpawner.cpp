#include "MonsterSpawner.h"
#include "Monster.h"
#include "Mob1.h"
#include "Mob2.h"
#include "Mob3.h"
#include "Mob4.h"
#include "Mob5.h"
#include "Mob6.h"
#include "SpacialMob.h"
#include "Random.h"
#include "GameManager.h"

void MonsterSpawner::Spawn(std::vector<Monster*>& box)
{
	Monster* mob1 = new ChangMinKong();
	Monster* mob2 = new BongJaeKong();
	Monster* mob3 = new JoEunKong();
	Monster* mob4 = new EunIlPerk();
	Monster* mob5 = new GeukMinKong();
	Monster* mob6 = new SeungHyeonSun();
	Monster* SpacialMob = new HoYeongJou();
	box.push_back(mob1);
	box.push_back(mob2);
	box.push_back(mob3);
	box.push_back(mob4);
	box.push_back(mob5);
	box.push_back(mob6);
	box.push_back(SpacialMob);
}