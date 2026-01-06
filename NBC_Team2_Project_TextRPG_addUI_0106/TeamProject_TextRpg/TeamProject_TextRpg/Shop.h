#pragma once
#include "Item.h"
#include <vector>
#include <memory>


class Character;

// TODO: [UI] UIManager 전방 선언
class UIManager;

class Shop
{
public:
	Shop() : bIsExit_(false) {};

	// TODO: 기존 runshop 주석처리 / 포인터 매개변수 추가
	// void RunShop(Character* Player);
	void RunShop(Character* player, UIManager* ui);

	void Initialize();
	void ShowItemList();

	// TODO: 기존 sellitem 주석처리 / 포인터 매개변수 추가
	// void SellItem(class Character* Player);
	// void BuyItem(class Character* Player);
	void SellItem(Character* player, UIManager* ui);
	void BuyItem(Character* player, UIManager* ui);

private:
	std::vector<std::unique_ptr<Item>> Product_;
	bool bIsExit_;
};

