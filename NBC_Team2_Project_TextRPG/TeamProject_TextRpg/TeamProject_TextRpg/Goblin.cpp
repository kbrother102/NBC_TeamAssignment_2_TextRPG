#include "Goblin.h"

void ChangMinKong::SpawnMob(int level)
{
	std::cout << "changmin 수업시작" << std::endl;
	// 몬스터가 살아있는지 체크
	if (bIsAlive_ == false)
	{
		//std::srand((unsigned int)time(NULL));

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(20, 30);

		health_ = (level * dis(rd));
		attack_ = (level * dis(rd));
		bIsAlive_ = true;

		std::cout << health_ << " " << attack_ << " " << std::endl;
	}
	else return;
}

void ChangMinKong::DieMob()
{

	if (bIsAlive_ == true)
	{
		bIsAlive_ = false;
		//사망 메세지 출력 후 경험치 골드 전달.
		std::cout << "고생하셨습니다 여러분 젭에서 뵈어요! 안녕~~" << std::endl;
	}
	else return;
}

void ChangMinKong::TakeDamaged(int damage)
{
	health_ -= damage;
	if (health_ <= 0);
}