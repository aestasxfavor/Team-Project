#pragma once
#include "Util.h"
#include "Player.h"
#include "EnemyManager.h"
#include "DropManager.h"
#include "UIManager.h"
#include "EffectManager.h"
#include "Map.h"

class Stage
{
	
public:
	Map map;
	Player* player;					// Player 관한 클래스 접근 시
	EnemyManager* enemyManager;		// 적 생성
	DropManager* dropManager;		// 적 죽이면 드랍되는 드랍아이템 관련
	UIManager* uiManager;			// UI 관련
	EffectManager* effectManager;	// 
	//킬카운트
	int killCount = 0;

	
	Stage()
	{
		player = nullptr;
		enemyManager = nullptr;
		dropManager = nullptr;
		uiManager = nullptr;
		effectManager = nullptr;
	}
	~Stage()
	{
		delete player;
		delete enemyManager;
		delete dropManager;
		delete uiManager;
		delete effectManager;
	}
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);

	//추가
	void HandlePlayerEnemyCollision();//충돌 Stage.cpp

private:
	sf::View view;

};


