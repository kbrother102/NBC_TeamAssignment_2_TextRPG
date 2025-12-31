#include "ChangMinKong.h"

void ChangMinKong::TakeDamaged(int damage)
{
	health_ -= damage;
	if (health_ <= 0);
}

void ChangMinKong::Buff()
{
	bIsBuff = true;
	attack_ *= 2;
	std::cout << "카메라를 안키셨군요" << std::endl;
}

void ChangMinKong::Attack()
{
	std::srand((unsigned int)time(NULL));
	if (rand() % 9 < 3 && bIsBuff == false)
	{
		Buff();
		std::cout << attack_ << std::endl;
	}
	else
	{
		if (bIsBuff == true)
		{
			//데미지 전달
			attack_ /= 2;
			bIsBuff = false;
		}
		// 데미지 전달
	}
	std::cout << bIsBuff << std::endl;
	std::cout << (rand() % 9) << std::endl;

}
