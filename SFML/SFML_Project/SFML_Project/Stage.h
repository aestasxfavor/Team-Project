#pragma once
#include "Util.h"
#include "Player.h"
#include "StageManager.h"
#include "DropManager.h"
#include "UIManager.h"
#include "EffectManager.h"
#include "Map.h"

class Stage 
{
	
public:
	Map map;
	Player* player;					// Player 관한 클래스 접근 시
	StageManager* stageManager;		// 효 추가 : Player+Enemy 둘다 관리하는 거
	DropManager* dropManager;		// 적 죽이면 드랍되는 드랍아이템 관련
	UIManager* uiManager;			// UI 관련

	EffectManager* effectManager;	// 2025-07-22 효 추가 : 이펙트는... 일단 보류하기

	//킬카운트
	static int killCount;

	Stage()
	{
		player = nullptr;
		stageManager = nullptr;
		dropManager = nullptr;
		uiManager = nullptr;
		effectManager = nullptr;
	}
	~Stage()
	{
		delete player;
		delete stageManager;
		delete dropManager;
		delete uiManager;
		delete effectManager;
	}
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);

	//추가 (2025-07-21 준호님 추가)
	void HandlePlayerEnemyCollision();//충돌 Stage.cpp

private:
	sf::View view;	// 카메라

};


