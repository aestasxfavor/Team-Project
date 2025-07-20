#pragma once
#include "Util.h"
#include "SFML/Graphics.hpp"

// 효 추가 : 공격력, 레벨, 스탯포인트 관리
// 기본 공격력 저장 


// 아래 Enum의 경우 이 클래스를 가져갈 Player 클래스에
// 옮겨야함.
// 현재 혹시 몰라서 남겨놓은 상태
enum class StatType
{
	MAXHP,          //최대체력
	DAMAGE,         //대미지
	ATTACKSPEED,    //공격속도
	DEFENSE,        //방어력
	CRITICAL,       //치명타율
	MOVESPEED,      //이동속도
	ATTACKRANGE,    //사정거리
	DEFAULT,        //초기화용 디폴트
};


class PlayerStats
{
public:
	// 기본 능력치
	int maxHp;          // 최대체력
	int currentHp;      // 현재체력
	int damage;         // 대미지
	float attackSpeed;  // 공격속도
	int defense;        // 방어력
	float critical;     // 치명타율
	int moveSpeed;      // 추가 이동속도

	//이거는 공격 로직에 맞춰서 변경이 필요함.
	sf::Vector2f attackRange;    // 사정거리

	int level;          // 레벨
	int exp;            // 목표경험치
	int currentExp;     // 현재경험치

	float baseAttackSpeed;		// 기본 공격속도
	float totalAttackSpeed;				// 모든 공격속도 백분율보너스 합계
public:
	struct StatOption           //선택지 옵션 구조체
	{
		std::string name;
		StatType type = StatType::DEFAULT;
		float amount = 0;
		std::string Grade;
	};
	const std::vector<StatOption> options = {
		{"체력 +10",StatType::MAXHP,10.f,"C"},
		{"체력 +20",StatType::MAXHP,20.f,"B"},
		{"체력 +30",StatType::MAXHP,30.f,"A"},
		{"공격력 +5",StatType::DAMAGE,5.f,"C"},
		{"공격력 +10",StatType::DAMAGE,10.f,"B"},
		{"공격력 +15",StatType::DAMAGE,15.f,"A"},
		{"공격속도 +7%",StatType::ATTACKSPEED,0.07f,"C"},
		{"공격속도 +10%",StatType::ATTACKSPEED,0.1f,"B"},
		{"공격속도 +15%",StatType::ATTACKSPEED,0.15f,"A"},
		{"방어력 +2",StatType::DEFENSE,2.f,"C"},
		{"방어력 +3",StatType::DEFENSE,3.f,"B"},
		{"방어력 +5",StatType::DEFENSE,5.f,"A"},
		{"치명타율 +3%",StatType::CRITICAL,0.03f,"C"},
		{"치명타율 +5%",StatType::CRITICAL,0.05f,"B"},
		{"치명타율 +7%",StatType::CRITICAL,0.07f,"A"},
		{"이동속도 +5%",StatType::MOVESPEED,0.05f,"C"},
		{"이동속도 +7%",StatType::MOVESPEED,0.07f,"B"},
		{"이동속도 +10%",StatType::MOVESPEED,0.1f,"A"},
		// 추후 사정거리 추가해야함.

	};  // 위 선택지 내용 담아둘 컨테이너

public:
	std::vector<StatOption> GetRandomChoices(const vector<StatOption>& pool, int count = 3);
	// 필요하다 생각되면 private로 빼도됨
	PlayerStats();
	~PlayerStats();

	// 레벨 관련

	void GainExp(int amount);           // 경험치획득
	void LevelUp();                     // 레벨 업

	// 스탯 적용 함수
	void ApplyStat(StatOption option);

	// 현재 스탯 상태 출력 or UI용 getter
	const int& GetLevel() const;


	// 공속 관련 함수
	void CalculateFinalAttackSpeed();	// 모든 스탯 변화 시 호출해서 최종 공격 속도 갱신 함수
	float GetFinalAttackCooldown() const; // 최종적으로 계산된 공격 쿨타임 반환(Player 클래스에서 사용할 예정)
	float GetAttackSpeedPercentageBonus() const { return totalAttackSpeed; }
};

