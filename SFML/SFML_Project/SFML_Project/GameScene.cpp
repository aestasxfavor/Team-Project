#include "GameScene.h"

GameScene::~GameScene()
{
	delete stage; // Stage 객체 삭제
}

void GameScene::Init()
{
	stage = new Stage();
	stage->Init();

	uiManager.Init(); // UI 매니저 초기화
	uiManager.StartWaveTimer(); // 웨이브 타이머 시작
	clock.restart();  // 시간 초기화
}

void GameScene::Update(sf::RenderWindow& window)
{
	float dt = clock.restart().asSeconds();  // 델타타임 계산
	stage->Update(dt);
	uiManager.Update(); // UI 매니저 업데이트

}

void GameScene::Render(sf::RenderWindow& window)
{
	stage->Render(window);
	uiManager.Render(window); // UI 매니저 렌더링
}
