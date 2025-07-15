#pragma once
#include "Util.h"
// 효 추가 : 공격력, 레벨, 스탯포인트 관리
// 기본 공격력 저장 
class PlayerStats
{
private:
    // 기본 능력치
    int baseAttack;
    int maxHp;
    int currentHp;
    int level;
    int exp;
    int expToNextLevel;
    int statPoints;
public:
    // 필요하다 생각되면 private로 빼도됨
    PlayerStats() {}
    ~PlayerStats();

    // 스탯 증가 함수
    void GainExp(int amount);
    void LevelUp();

    // 스탯 적용
    void AddAttack(int amount);
    void AddMaxHp(int amount);

    // 레벨업 가능 여부
    bool CanLevelUp() const;

    // 현재 스탯 상태 출력 or UI용 getter
    int GetAttack() const;
    int GetLevel() const;
};

