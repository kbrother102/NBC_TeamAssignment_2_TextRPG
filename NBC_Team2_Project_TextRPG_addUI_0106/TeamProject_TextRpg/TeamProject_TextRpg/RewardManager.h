#pragma once
class Creature;
class Monster;
class Character;

class RewardManager
{
public: 
    void ProcessReward(Monster* Monster, Character* Player);
    //싱글턴 패턴 - getinstance로 객체생성
    static RewardManager& GetInstance();

    //싱글턴 패턴을 위한 복사생성자, 대입연산자 삭제
    RewardManager(const RewardManager&)= delete;
    void operator=(const RewardManager&) = delete;
private:
    //싱글턴패턴 : 생성자를 프라이빗으로
    RewardManager() {};

    //내부계산용 함수
    bool isItemDrop();

    enum ItemType {
        HealthPotion,
        AttackBoost
    };


};

