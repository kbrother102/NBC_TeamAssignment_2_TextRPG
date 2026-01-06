#pragma once
#include "Item.h"
#include <vector>
#include <memory>

class Item;
class StatComponent;

class Inventory
{
public://직접 아이템을 사용하기 위한 함수
	bool AddItem(std::unique_ptr<Item> item);
	bool UseItem(int index, StatComponent& stats_);

	//int GetGold() const;
	//void AddGold(int amount);
	//bool SpendGold(int amount);

	std::string GetItemName(int index) const;
	

	//모든 원소가 nullptr 일 경우 true 하나라도 템이 있으면 false를 반환하는 함수
	bool IsEmpty() const;
	
	//Shop과 연계되는 함수 sell은 반환이 필요하니(판매 가능?불가능?) bool로 전환이 더 유리
	void RemoveItem(int index);
	int GetItemCount() const;
	const Item* GetItem(int index) const;
//	Item* GetItem(int index); // 만약 아이템의 수정이 필요해지면 주석 해제

private:
	std::vector<std::unique_ptr<Item>> items_;
	//int Gold_ = 0;
};