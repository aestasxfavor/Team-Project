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
    sf::Clock clock; // 시간 측정용 시계
public:
    ~GameScene();
public:
    void Init() override;
    void Update(sf::RenderWindow& window) override;
    void Render(sf::RenderWindow& window) override;
};