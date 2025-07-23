#pragma once
#include "Util.h"
#include "Scene.h"

// 2025-07-23 효 추가: 게임 씬 클래스 정의
class GameScene : public Scene
{
public:
    void Init() override;
    void Update(sf::RenderWindow& window) override;
    void Render(sf::RenderWindow& window) override;
};