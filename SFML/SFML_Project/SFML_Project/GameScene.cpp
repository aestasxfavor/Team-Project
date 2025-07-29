#include "GameScene.h"
#include "PlayerStats.h"
#include "SoundManager.h"

GameScene::~GameScene()
{
	delete stage; // Stage 객체 삭제
}

void GameScene::Init()
{
	if (soundManager.LoadBGM(GetSoundPath("Stage_BGM_1.wav")))
	{
		soundManager.PlayBGM(true);
	}
	uiManager.Init(); // UI 매니저 초기화
	stage = new Stage();  //  반드시 먼저 해줘야 함
	stage->Init();
	stage->stageManager->SetUIManager(&uiManager); // StageManager에 UI 매니저 설정
	stage->player->uiManager = &uiManager;

	stage->stageManager->NextWave(*stage->player, uiManager, -1, {}); // 첫 웨이브 수 증가
	uiManager.ShowWaveText(stage->stageManager->GetCurrentWave()); // 웨이브 1 표시

	uiManager.SetPlayer(stage->player); // 플레이어 설정 (UI 매니저에 플레이어 설정)

	uiManager.ResetWaveTimer(); // 그리고 나서 타이머 시작

	clock.restart();  // 시간 초기화

	// 상점 UI 콜백 등록 (딱 한 번만 하면 됨)
	uiManager.shopUI.SetOnSelect([this](int selectedIndex)
		{
			std::cout << "Selected Option : " << selectedIndex << std::endl;

			uiManager.shopUI.Close();

			// -1은 "닫기 버튼 누름"
			if (selectedIndex != -1)
			{
				// 아이템 적용 로직 여기에!
			}

			// 어쨌든 다음 웨이브는 시작
			selectedStatChoices = uiManager.shopUI.GetSelectedChoices();		// 텍스트가 안나왓던 이유 : 이걸 안써줌;;;;;
			stage->stageManager->NextWave(*stage->player, uiManager, selectedIndex, selectedStatChoices);
			uiManager.ResetWaveTimer();
			uiManager.ShowWaveText(stage->stageManager->GetCurrentWave());
		});
}

void GameScene::Update(sf::RenderWindow& window)
{
	float dt = clock.restart().asSeconds();  // 델타타임 계산

	// 0. 상점이 열려있으면 게임 로직 정지 + 상태 업데이트
	if (uiManager.IsShopOpen())
	{
		sf::Vector2f mousePos = window.mapPixelToCoords(
			sf::Mouse::getPosition(window),
			window.getDefaultView()  // 이거 추가!
		);

		bool nowMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool isClick = !prevMousePressed && nowMousePressed;  // 눌렀을 때 딱 한 번만 true

		uiManager.UpdateShop(mousePos, isClick);

		prevMousePressed = nowMousePressed;  // 마지막에 상태 저장
		wasShopOpen = true;
		return;
	}

	// 1. 상점이 막 닫혔으면 → 다음 웨이브 시작
	if (wasShopOpen && !uiManager.IsShopOpen())
	{
		/*stage->stageManager->NextWave();
		uiManager.ResetWaveTimer();
		uiManager.ShowWaveText(stage->stageManager->GetCurrentWave());*/
	}

	// 2. 웨이브 종료 타이머 (30초)
	if (!waveEnded && uiManager.GetWaveElapsedTime() >= 30.f)
	{
		waveEnded = true;
		waveEndTimer = 0.f;
	}

	// 3. 상점 열기 지연
	if (waveEnded)
	{
		waveEndTimer += dt;

		if (waveEndTimer >= 1.f)
		{
			uiManager.OpenShop(*stage->player->stats);
			waveEnded = false;
		}

		return;
	}

	// 4. 일반 게임 업데이트
	stage->Update(dt);
	uiManager.Update(dt);

	// 5. 마지막에 상점 상태 저장
	wasShopOpen = false;

}

void GameScene::Render(sf::RenderWindow& window)
{
	stage->Render(window);
	uiManager.Render(window); // UI 매니저 렌더링
}

void GameScene::ResetGame()
{
	std::cout << "[리셋됨] GameScene::ResetGame() 호출됨!" << std::endl;
	delete stage;
	stage = new Stage();
	stage->Init();

	uiManager.Init();
	stage->stageManager->SetUIManager(&uiManager);
	stage->player->uiManager = &uiManager;

	stage->stageManager->NextWave(*stage->player, uiManager, -1, {});
	uiManager.ShowWaveText(stage->stageManager->GetCurrentWave());
	uiManager.SetPlayer(stage->player);

	uiManager.ResetWaveTimer();
	clock.restart();

	waveEnded = false;
	waveEndTimer = 0.f;
	wasShopOpen = false;
	prevMousePressed = false;

	if (stage->player->stats)
		stage->player->stats->Reset();

	Stage::killCount = 0;

	// 상점 콜백도 다시 등록
	uiManager.shopUI.SetOnSelect([this](int selectedIndex)
		{
			std::cout << "Selected Option : " << selectedIndex << std::endl;
			uiManager.shopUI.Close();

			if (selectedIndex != -1)
			{
				// 선택 능력 적용 로직
			}

			selectedStatChoices = uiManager.shopUI.GetSelectedChoices();
			stage->stageManager->NextWave(*stage->player, uiManager, selectedIndex, selectedStatChoices);
			uiManager.ResetWaveTimer();
			uiManager.ShowWaveText(stage->stageManager->GetCurrentWave());
		});
}
