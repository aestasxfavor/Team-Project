#pragma once
#include "Util.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Skill.h"
#include "PlayerStats.h"

class Player
{

public:
	int hp, level, exp;
	// 효 추가(개인적인 생각) : hp = 20(기본), level, exp = 0 기본설정하면 될거같습니당
	float x, y;				// 지워도 됨.
	float speed, attackDMG, critical;

	Inventory* inven;
	std::vector<Weapon*> weapons;
	Skill* skillSlots[4]; // qwer 또는 1234

	sf::Texture texture;
	sf::Sprite spritePlayer;
	enum State { IDLE, MOVE } state = IDLE;


	// 미니 추가 
	// PlayerStat관련 함수 및 변수임
	PlayerStats stats;
	float currentAttackCoolTime; // 현재 공격 쿨타임
	bool canAttack; // 공격 가능한 상태인지? 체크 변수

				// 이거 생성자 Cpp로 옮길 시 같이 옮겨 주세엽
	Player(): stats(),currentAttackCoolTime(0.0f),canAttack(true)
	{
		
	}
	~Player()
	{

	}

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);
	void Move(float deltaTime, const sf::Vector2f& dir);
	void PickUp();
	void LevelUp(); // 미니 추가 : 이거 안써도 될 듯?? PlayerStat에서 하니까
	void Attack();
	void UseSkill(int slot); // 키 입력 받고 키를 매개변수로 해당하는 값에 따라 스킬 실행
							 // update안에다가 키입력 조건 걸어서 UseSkill() 해놓고 누른 버튼 변환해서 또는 enum으로
							 // 그 인수를 int slot으로 넣기

	// 미니가 추가한 함수
	// 아이템 먹고 경험치 얻을 때 함수
	void GainExperience(int amount);
	void AddItemStat(const PlayerStats::StatOption itemStats);

	//추가
	sf::Vector2f GetPosition() const;
	void Render(sf::RenderWindow& window, const sf::Vector2f& position);

	sf::FloatRect GetGlobalBounds() const;//충돌관련
	void TakeDamage(int amount);//충돌시 받는 피해

	//피격시 무적
	bool isInvincible = false;
	float invincibleTimer = 0.f;
	float invincibleDuration = 1.0f;//피격시 1초무족
	//깜빡이기
	float blinkTimer = 0.f;
	float blinkInterval = 0.1f; // 0.1초마다 깜빡
	bool visible = true; // 현재 보이는 상태
private:
	float animationTimer = 0.f;   // 누적된 애니메이션 시간
	float frameDuration = 0.2f;   // 한 프레임당 지속 시간 (초)
	int currentFrame = 0;
	//추가
	std::vector<sf::IntRect> walkFrames;
};

