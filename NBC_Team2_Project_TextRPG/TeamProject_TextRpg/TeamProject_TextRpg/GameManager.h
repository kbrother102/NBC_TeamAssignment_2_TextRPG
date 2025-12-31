#pragma once
class Character;
class Monster;

class GameManager
{
public:
    void Run();
    Monster* GenerateMonster(int Level);
    void Battle(Character* player);
    void DisplayInventory(Character* player);

private:
    // 게임 시작
    void StartGame();
    // 플레이어 입력 로직
    void PlayerInputLogic();
    // 캐릭터 생성
    void CreateCharacter();
    // 몬스터 생성
    void GenerateMonster();

};

