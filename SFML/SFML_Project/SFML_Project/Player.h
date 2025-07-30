#pragma once
#include "Util.h"

#include "PlayerStats.h"

// 전방선언햇는데 얘네가 왜 잇어야하는지.. 모르겟음 판단 보류
#include "Enemy.h"
#include "Spear.h"
#include "Bullet.h"

class SceneManager; // 전방 선언: SceneManager 클래스 필요
class UIManager; // 전방 선언: UIManager 클래스 필요


class Enemy;
class Spear;
class Bullet;

class Player
{
public:
	float speed;
	Spear* spear = nullptr;
	float spearCoolTime = 0.f;

	UIManager* uiManager = nullptr; // UI 매니저 포인터 (has - a 관계)
	

	sf::Texture texture;
	sf::Sprite spritePlayer;
	enum State { IDLE, MOVE } state = IDLE;

	bool isDead = false; // 플레이어가 죽었는지 여부


	// 미니 추가 
	// PlayerStat관련 함수 및 변수임
	PlayerStats * stats;
	float currentAttackCoolTime; // 현재 공격 쿨타임
	std::vector<Bullet*> bullets;

				// 이거 생성자 Cpp로 옮길 시 같이 옮겨 주세엽		// 2025-07-24 01:13분 효 추가 : 이거 옮길 필요가..있나? 일단 보류 내일 상의해서 하기 
	Player(): stats(nullptr),currentAttackCoolTime(0.0f)
	{
	}
	~Player()
	{
		delete stats;
		// 소멸자 구현잇다가 하고 
	}

	void Init();
	void Update(float deltaTime, const std::vector<Enemy*>& enemies);
	void Render(sf::RenderWindow& window);
	void Move(float deltaTime, const sf::Vector2f& dir);
	void PickUp();
	void LevelUp(); // 미니 추가 : 이거 안써도 될 듯?? PlayerStat에서 하니까

	void Attack();
	
	void Death(); // 플레이어가 죽었을 때 호출되는 함수

	void Attack(const std::vector<Enemy*>& enemies);

	void Reset(); // 플레이어 상태 초기화 함수

	// 미니가 추가한 함수
	// 아이템 먹고 경험치 얻을 때 함수
	void GainExperience();
	void AddItemStat(const PlayerStats::StatOption itemStats);

	//추가
	sf::Vector2f GetPosition() const;
	void Render(sf::RenderWindow& window, const sf::Vector2f& position);

	sf::FloatRect GetGlobalBounds() const;//충돌관련
	void TakeDamage(int amount);//충돌시 받는 피해

	//피격시 무적
	bool isInvincible = false;
	float invincibleTimer = 0.f;
	float invincibleDuration = 1.0f;//피격시 1초 무적
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

