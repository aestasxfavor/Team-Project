#pragma once
#include "Util.h"
#include "Player.h"
#include "StageManager.h"
#include "UIManager.h"
#include "Map.h"

class Stage 
{
	
public:
	Map map;
	Player* player;					// Player 관한 클래스 접근 시
	StageManager* stageManager;		// 효 추가 : Player+Enemy 둘다 관리하는 거
	UIManager* uiManager;			// UI 관련

	//킬카운트
	static int killCount;

	Stage();						// 생성자
	~Stage();						// 소멸자
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);

	//추가 (2025-07-21 준호님 추가)
	void HandlePlayerEnemyCollision();//충돌 Stage.cpp

private:
	sf::View view;	// 카메라

};


