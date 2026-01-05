#include "Inventory.h"
#include "Item.h"

bool Inventory::AddItem(std::unique_ptr<Item> item)
{
	if (!item)
	{
		return false;
	}
	//빈칸이 있다면 우선 대입
	for (auto& slot : items_)
	{
		if (slot == nullptr)
		{
			slot = std::move(item);
			return true;
		}
	}
	//빈칸이 없으면 뒤에 추가
	items_.push_back(std::move(item));
	{
		return true;
	}
}

bool Inventory::UseItem(int index, StatComponent& stats)
{
	if (index < 0 || index >= items_.size())
	{
		return false;
	}
	if (!items_[index])
	{
		return false;
	}

	bool used = items_[index]->Use(stats);
	if (used)
	{	//해당 자리를 null로 대체
		items_[index].reset();
	}
	return used;
}

std::string Inventory::GetItemName(int index) const
{	//아이템 영역 밖일때 예외 우선 처리
	if (index < 0 || index >= items_.size())
	{
		return "잘못된 수입니다.";
	}
	if (!items_[index])
	{
		return "빈칸입니다.";
	}
	return  items_[index]->GetName();
}

bool Inventory::IsEmpty() const
{
	for (const auto& item : items_) // 모든 아이템을 하나씩 꺼내서
	{
		if (item != nullptr) // "어? 물건이 하나라도 들어있네?"
		{
			return false; // 그럼 텅 빈 게 아님! (함수 즉시 종료)
		}
	}

	// 끝까지 다 뒤져봤는데 전부 nullptr이었다면
	return true;

}

int Inventory::GetItemCount() const
{	//아이템의 개수 반환
	return static_cast<int>(items_.size());
}

const Item* Inventory::GetItem(int index) const
{	//유효 범위 체크
	if (index < 0 || index >= items_.size())
	{
		return nullptr;
	}
	return items_[index].get();
}

//Item* Inventory::GetItem(int index)  //만약 아이템 수정이 필요해지면 주석 해제(내구도 등)
//{	//유효 범위 체크
//	if (index < 0 || index >= items_.size())
//	{
//		return nullptr;
//	}
//	return items_[index].get();
//}

void Inventory::RemoveItem(int index)
{	//유효 범위 체크
	if (index < 0 || index >= items_.size())
	{
		return;
	}
	items_[index].reset();//nullptr로 제거
}