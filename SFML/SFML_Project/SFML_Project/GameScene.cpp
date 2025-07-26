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
	stage->stageManager->SetUIManager(&uiManager); // StageManager에 UI 매니저 설정

	stage->stageManager->NextWave(); // 첫 웨이브 수 증가
	uiManager.ShowWaveText(stage->stageManager->GetCurrentWave()); // 웨이브 1 표시

	uiManager.ResetWaveTimer(); // 그리고 나서 타이머 시작

	clock.restart();  // 시간 초기화
}

void GameScene::Update(sf::RenderWindow& window)
{
	float dt = clock.restart().asSeconds();  // 델타타임 계산

	if (uiManager.GetWaveElapsedTime() >= 30.f)
	{
		stage->stageManager->NextWave(); // 웨이브 숫자 올리기
		uiManager.ResetWaveTimer();      // 타이머 리셋
		uiManager.ShowWaveText(stage->stageManager->GetCurrentWave()); // 웨이브 텍스트 보여주기
	}

	stage->Update(dt);
	uiManager.Update(dt); // UI 매니저 업데이트

	

}

void GameScene::Render(sf::RenderWindow& window)
{
	stage->Render(window);
	uiManager.Render(window); // UI 매니저 렌더링
}
 