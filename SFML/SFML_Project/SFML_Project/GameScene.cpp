#include "GameScene.h"
#include "PlayerStats.h"
#include "SoundManager.h"
#include "TitleScene.h"

GameScene::GameScene()
{
	game = new Game();   // ← 게임 상태 초기화
	player = nullptr;
	stage = nullptr;
	stageManager = nullptr;
	sceneManager = nullptr;
}


GameScene::~GameScene()
{
	delete game;
	delete stage;
}


void GameScene::Init()
{
	game->Reset(); // 전체 게임 상태 초기화

	if (soundManager.LoadBGM(GetSoundPath("Stage_BGM_1.wav")))
		soundManager.PlayBGM(true);

	uiManager.Init();
	uiManager.InitPauseUI();

	stage = new Stage();
	stage->Init();
	stage->stageManager->SetUIManager(&uiManager);
	stage->player->uiManager = &uiManager;

	// 초기 웨이브 설정
	stage->stageManager->NextWave(*stage->player, uiManager, -1, {});
	game->SetWave(stage->stageManager->GetCurrentWave());

	uiManager.ShowWaveText(game->GetWave());
	uiManager.SetPlayer(stage->player);
	uiManager.ResetWaveTimer();

	clock.restart();

	// 상점 선택 콜백
	uiManager.shopUI.SetOnSelect([this](int selectedIndex)
		{
			uiManager.shopUI.Close();

			if (selectedIndex != -1)
			{
				game->SetSelectedChoices(uiManager.shopUI.GetSelectedChoices());
			}

			stage->stageManager->NextWave(*stage->player, uiManager, selectedIndex, game->GetSelectedChoices());
			game->NextWave();
			uiManager.ShowWaveText(game->GetWave());
			uiManager.ResetWaveTimer();
		});
}


void GameScene::Update(sf::RenderWindow& window)
{
    float dt = 0.f;

    // 1. ESC 눌러서 일시정지 토글
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !prevEscPressed)
    {
        game->SetPaused(!game->IsPaused());
        if (game->IsPaused())
            uiManager.PauseWaveTimer();
        else
            uiManager.ResumeWaveTimer();
        prevEscPressed = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        prevEscPressed = false;
    }

    // 2. 일시정지 상태이면 일시정지 UI만 처리
    if (game->IsPaused())
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getDefaultView());
        bool nowMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        bool isClick = !prevMousePressed && nowMousePressed;

        if (isClick)
        {
            if (uiManager.IsMouseOverResume(mousePos))
            {
                game->SetPaused(false);
                uiManager.ResumeWaveTimer();
            }
            else if (uiManager.IsMouseOverExit(mousePos))
            {
                sceneManager->ChangeScene("Title");
            }
        }

        prevMousePressed = nowMousePressed;
        return;  // 게임 로직 정지
    }

    // 3. 시간 갱신
    dt = clock.restart().asSeconds();

    // 4. 상점 열려있으면 그쪽만 처리
    if (uiManager.IsShopOpen())
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getDefaultView());
        bool nowMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        bool isClick = !prevMousePressed && nowMousePressed;

        uiManager.UpdateShop(mousePos, isClick);
        prevMousePressed = nowMousePressed;
        wasShopOpen = true;
        return;
    }

    // 5. 상점 막 닫힌 직후 처리 (필요 시 작성)
    if (wasShopOpen && !uiManager.IsShopOpen())
    {
        // do nothing for now
    }

    // 6. 웨이브 종료 체크
    if (!waveEnded && uiManager.GetWaveElapsedTime() >= 30.f)
    {
        waveEnded = true;
        waveEndTimer = 0.f;
    }

    // 7. 웨이브 종료 후 1초 뒤 상점 열기
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

    // 8. 게임 로직 실행
    stage->Update(dt);
    uiManager.Update(dt);

    // 9. 상점 상태 기록
    wasShopOpen = false;
}



void GameScene::Render(sf::RenderWindow& window)
{
    stage->Render(window);             // 게임 씬의 스테이지(플레이어/적 등) 그리기
    uiManager.Render(window);          // 체력, 경험치, 시간 등 UI 그리기

    if (game->IsPaused())              // 게임 상태에서 pause 확인
        uiManager.RenderPauseUI(window); // 일시정지 UI 그리기

}

void GameScene::ResetGame()
{
	cout << "[리셋됨] GameScene::ResetGame() 호출됨" << endl;

	game->Reset();
	uiManager.ClearStatLog();

	delete stage;
	stage = new Stage();
	stage->Init();
	stage->stageManager->SetUIManager(&uiManager);
	stage->player->uiManager = &uiManager;

	stage->stageManager->SetResetting(true);
	stage->stageManager->NextWave(*stage->player, uiManager, -1, {});
	stage->stageManager->SetResetting(false);

	game->SetWave(stage->stageManager->GetCurrentWave());
	uiManager.ShowWaveText(game->GetWave());
	uiManager.SetPlayer(stage->player);
	uiManager.ResetWaveTimer();
	uiManager.SetPaused(false);
	uiManager.InitShop(*stage->player->stats);
	clock.restart();

	stage->player->stats->Reset();
	stage->player->SetPosition({ 960.f, 540.f });

	uiManager.shopUI.ClearSelectedChoices();

	// 상점 콜백 다시 등록
	uiManager.shopUI.SetOnSelect([this](int selectedIndex)
		{
			uiManager.shopUI.Close();

			if (selectedIndex != -1)
			{
				game->SetSelectedChoices(uiManager.shopUI.GetSelectedChoices());
			}

			stage->stageManager->NextWave(*stage->player, uiManager, selectedIndex, game->GetSelectedChoices());
			game->NextWave();
			uiManager.ShowWaveText(game->GetWave());
			uiManager.ResetWaveTimer();
		});
}
