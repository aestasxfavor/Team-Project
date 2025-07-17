#pragma once
#include "Util.h"
#include "Scene.h"
#include "Player.h"
#include "EnemyManager.h"
#include "CameraManager.h"

class GameScene : public Scene 
{
    Player* player;
    EnemyManager* enemyManager;
    CameraManager* camera;
public:
    void init() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};
