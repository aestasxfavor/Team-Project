#pragma once
#include "Util.h"
#include "Scene.h"
#include "Stage.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Game.h"

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
    SceneManager* sceneManager; // 씬 매니저
    Game* game; // 전체 게임 상태 담당

    sf::Clock clock; // 시간 측정용 시계

    bool waveEnded = false;
    float waveEndTimer = 0.f;

    bool wasShopOpen = false;  // 직전 프레임 상점 상태 기억용
    bool prevMousePressed = false;  // 클래스 멤버에 선언

    bool prevEscPressed = false;
    bool wasPausedBefore = false;

public:
    GameScene();
    ~GameScene();

    void Init() override;
    void Update(sf::RenderWindow& window) override;
    void Render(sf::RenderWindow& window) override;
    void ResetGame();
};