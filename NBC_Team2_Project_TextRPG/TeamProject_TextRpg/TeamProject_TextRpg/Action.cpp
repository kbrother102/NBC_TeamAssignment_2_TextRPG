#include "Action.h"
#include "Monster.h"
#include "Character.h"
#include "Item.h"
#include "Creature.h"
#include "Inventory.h"
#include "StatComponent.h"
#include "Random.h"
#include "Logger.h"
#include <string>



//공격.
void Action::Attack(Creature* target)
{
    //없으면 종료
    
    if(owner_ == nullptr || target == nullptr)
  {
        Logger::Add(LogType::WARNING, "(owner_ == nullptr || target == nullptr");
      return;
  }
	
	
    
	//이름이 비어있으면 종료
    if(owner_->GetName() == "" || target->GetName() == "")
    {
        Logger::Add(LogType::WARNING, "이름이 없습니다.");
        return;
	}
	StatComponent* ownerStats = owner_->GetStatComponent();
	StatComponent* targetStats = target->GetStatComponent();
	//죽은 상태면 종료
    if (ownerStats->GetIsDead() || targetStats->GetIsDead())
    {
        Logger::Add(LogType::WARNING, "플레이어나 타겟 no.");
        return;
    }
   

	//TODO: 타입을 받아서 플레이어와 몬스터가 공격했을 때 로그 다르게 출력,이,가 나눠서 출력. 
    //if(ownerStats->GetType == "")
    //로그 공격했다 구현
	Logger::Add(LogType::COMBAT, "==================================");
    Logger::Add(LogType::COMBAT, owner_->GetName()+ "가 "+ target->GetName()+ "을(를) 공격했다! ");
    Logger::Add(LogType::COMBAT, "데미지 : " + std::to_string(ownerStats->GetAttack()));
	Logger::Add(LogType::COMBAT, target->GetName() + "의 남은 체력 : " + std::to_string(targetStats->GetHp()) + " ");
    Logger::Add(LogType::COMBAT, "==================================");
    //타겟의 체력에서 공격자의 공격력만큼 차감//여기 대미지 계산확실하게
    target->TakeDamage(ownerStats->GetAttack());
    
}


//아이템 획득.
void Action::RandUseItem()
{
    
    Character* player = dynamic_cast<Character*>(owner_);
	//플레이어가 아니면 종료
    if (!player)
    {
        return;
    }

    // 인벤토리 없으면 종료
    Inventory* inventory = player->GetInventory();
    if(inventory == nullptr)
    {
        return;
	}
    
	//아이템 개수가 0인지 체크
    if (inventory->GetItemCount() == 0)   
     {
          return;
     }
	//TODO: 30% 확률로 아이템 사용한 뒤 로그 출력
	//0~99까지 일정한 확률 랜덤 생성
    int r = Random::GetRandInt(0, 99);
   
    if (r < 30)
    {

        //인벤토리에서 0~에서 인벤토리 사이즈만큼의 랜덤을 돌려 아이템 선택;
       int random = Random::GetRandInt(0, inventory->GetItemCount()-1);
        //아이템을 랜덤으로 선택한것을 저장.
       const Item* item = inventory->GetItem(random);
	   std::string itemName = item->GetName();
	   StatComponent* stats = owner_->GetStatComponent();
        if(!item)
        {
            return;
		}

        if(stats->GetMaxHp() == stats->GetHp() && itemName == "회복 포션")
        {
            return;
		}
		int beforeAttack = stats->GetAttack();
        inventory->UseItem(random, *owner_->GetStatComponent());

        //로그 아이템을 사용했다 구현
        if (itemName == "회복 포션")
        {
			Logger::Add(LogType::INFO, "체력이 회복되었다!" );
			Logger::Add(LogType::INFO, std::to_string(stats->GetMaxHp()) +" : " + std::to_string(stats->GetHp()));
        }

        if (itemName == "공격력 증폭제")
        {
            Logger::Add(LogType::INFO, "코딩력이 증가했다!");
			Logger::Add(LogType::INFO, std::to_string(beforeAttack) + "-> " + std::to_string(stats->GetAttack()));
        }
        Logger::Add(LogType::INFO, owner_->GetName() + "가 " + itemName + "을(를) 사용했다!");
        

    }
}
//죽음.
void Action::Die()
{
    //없으면 종료
    if(owner_ == nullptr)
    {
        return;
    }

    //사망.
	owner_->GetStatComponent()->SetIsDead(true);

	//로그 사망했다 구현    
	//TODO: 타입을 받아서 플레이어와 몬스터가 죽었을 때 로그 다르게 출력
    Logger::Add(LogType::INFO,(owner_->GetName()) + "의 과제를 완료했다.");

    //각자의 네임코드를 가져와 출력(미정)
    //if(owner_->GetName() == "Monster")
    //{
    //    Logger::Add(LogType::INFO, "몬스터가 죽었습니다.");
	//}
    //else if (owner_->GetName() == "Player")
    //{
    //    Logger::Add(LogType::INFO, "몬스터가 죽었습니다.");
    //}
}





