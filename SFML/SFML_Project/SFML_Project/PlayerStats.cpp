#include "PlayerStats.h"
#include <algorithm>
#include <random>
#include "Stage.h"

vector<PlayerStats::StatOption> PlayerStats::GetRandomChoices(const vector<StatOption>& pool, int count)
{
	vector<StatOption> temp = pool;
	shuffle(temp.begin(), temp.end(), mt19937{ random_device{}() });
	temp.resize(count);

	// stat구조체의 정보들을 담은 자료구조를 복사해서
	// 배열 순서를 shuffle 시켜서
	// resize를 통해 앞 열 3개만 남겨놓기

	// 근데 이렇게 하면 외부에서 statOption으로 접근은 불가한 로직임
	return temp;
}


void PlayerStats::GainExp()
{
	currentExp = Stage::killCount;
	//currentExp ++;  // Stage::killCount는 현재 스테이지에서 처치한 적의 수
	//cout << "CurrenExp : " << currentExp << endl;
	if (Stage::killCount >= exp) LevelUp();   // 경험치가 다차면 레벨업
}

void PlayerStats::LevelUp()
{
	level++;
	currentExp = 0;
	Stage::killCount = 0;  // 0으로 다시 초기화
	exp = exp + exp;
	cout  << level << "레벨이 되었습니다 !!!" << endl;     //작동 확인 용 추후 삭제바람.


	// 레벨업 시 PlayerStats::CalculateFinalAttackSpeed()가 호출될 필요는 없을 듯?
	// 왜냐면 뭐 레벨업 할때 스탯 증가 같은걸 할 예정이라면 필요한데 안할 거 같아서...?
	// 
	// 뭐 만약 추가를 한다면 아래와 같이 작성할 것 미래의 김동민이여
	// 
	// 예를 들어, 레벨업 시 "공격 속도 1% 증가" 스탯을 자동으로 받는 경우:
	// PlayerStats::StatOption levelUpASBonus;
	// levelUpASBonus.type = StatType::ATTACKSPEED;
	// levelUpASBonus.amount = 0.01f; // 1% 증가
	// m_stats.ApplyStat(levelUpASBonus);
}

void PlayerStats::ApplyStat(StatOption option)
{
	switch (option.type)
	{
	case StatType::MAXHP:			maxHp += option.amount; break;
	case StatType::DAMAGE:			damage += option.amount; break;
	case StatType::ATTACKSPEED:		attackSpeed += option.amount; break;
	case StatType::DEFENSE:			defense += option.amount; break;
	case StatType::CRITICAL:		critical += option.amount; break;
	case StatType::MOVESPEED:		moveSpeed += option.amount; break;
	case StatType::ATTACKRANGE:		break; // 이건 나중에 생각하자.
	case StatType::DEFAULT:			break;
	}
	
	if (option.type == StatType::ATTACKSPEED)
	{
		CalculateFinalAttackSpeed();
	}
}

const int& PlayerStats::GetLevel() const
{
	return level;
}

void PlayerStats::CalculateFinalAttackSpeed()
{
	// 공식 이해를 위한 주석입니다.
	// APS == Attack Per Second 
	// FinalAPS = BaseAPS * ( 1 + TotalAttackSpeed / 100.0f)

	float finalAPS = baseAttackSpeed * (1.0f + totalAttackSpeed / 100.0f);

	attackSpeed = finalAPS;
}

float PlayerStats::GetFinalAttackCooldown() const
{
	// 최종 APS가 0보다 클 때만
	// 즉 안전장치
	if (attackSpeed > 0)
	{
		return 1.0f / attackSpeed;
	}
	return 99999.0f; // 공격 불가 또는 매우 긴 쿨타임.
}

void PlayerStats::Reset()
{
	maxHp = 100;
	currentHp = 100;		// 플레이어 기본 체력 
	damage = 5;
	attackSpeed = 1.0f;
	defense = 0;
	critical = 0.0f;
	moveSpeed = 1.0f;
	attackRange = { 4.0f, 4.0f };
	level = 1;
	exp = 50;
	currentExp = 0;

	baseAttackSpeed = 1.0f;			//기본 공속 상태
	totalAttackSpeed = 0.0f;		//추가 공속이라 없는 상태
}

PlayerStats::PlayerStats()
{
	maxHp = 100;
	currentHp = 100;		// 플레이어 기본 체력 
	damage = 5;
	attackSpeed = 1.0f;
	defense = 0;
	critical = 0.0f;
	moveSpeed = 1.0f;
	attackRange = { 4.0f, 4.0f };
	level = 1;
	exp = 50;
	currentExp = 0;

	baseAttackSpeed = 1.0f;			//기본 공속 상태
	totalAttackSpeed = 0.0f;		//추가 공속이라 없는 상태
}

PlayerStats::~PlayerStats()
{
	//딱히 할 게 있나? 싶은 데 고민 좀
}