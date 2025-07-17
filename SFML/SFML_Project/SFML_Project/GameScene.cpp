#include "GameScene.h"

// 병합 양식 
//void GameScene::init()
//{
//    player = new Player();
//    enemyManager = new EnemyManager();
//    camera = new CameraManager(window, player);
//    waveManager = new WaveManager();
//    dropManager = new DropManager();
//    uiManager = new UIManager();
//}
//
//void GameScene::update(float dt)
//{
//    player->update(dt);
//    enemyManager->update(dt, player->getPosition());
//    camera->update(dt);
//    waveManager->update(dt);
//    dropManager->update(dt, player);
//    uiManager->update(player->getStats(), waveManager->getTimeLeft());
//}
//
//void GameScene::render(sf::RenderWindow& window)
//{
//    window.setView(camera->getView());
//
//    player->render(window);
//    enemyManager->render(window);
//    dropManager->render(window);
//    uiManager->render(window);
//}
