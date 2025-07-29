#pragma once
#include "Util.h"
#include "Scene.h"
#include "Stage.h"
#include "UIManager.h"


static float deltaTime = 0.f;

// 2025-07-23 효 추가: 게임 씬 클래스 정의
class GameScene : public Scene
{
private:
	UIManager uiManager; // UI 매니저
    Stage* stage;
    Player* player;
    StageManager* stageManager;
    PlayerStats playerStats;
	
   
    sf::Clock clock; // 시간 측정용 시계

    int selectedIndex = -1;
    vector<PlayerStats::StatOption> selectedStatChoices;


	// wave 끝났는지 여부
    bool waveEnded = false;
    float waveEndTimer = 0.f;

    bool wasShopOpen = false;  // 직전 프레임 상점 상태 기억용
    bool prevMousePressed = false;  // 클래스 멤버에 선언


public:
    ~GameScene();
public:
    void Init() override;
    void Update(sf::RenderWindow& window) override;
    void Render(sf::RenderWindow& window) override;
    void ResetGame();
};