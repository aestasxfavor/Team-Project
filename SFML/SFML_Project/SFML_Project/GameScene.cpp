#include "GameScene.h"
#include "PlayerStats.h"
#include "SoundManager.h"
#include "TitleScene.h"

GameScene::GameScene()
{
	player = nullptr; // 플레이어 초기화
	stage = nullptr; // Stage 객체 초기화
	stageManager = nullptr; // StageManager 객체 초기화
	sceneManager = nullptr;
}

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
	uiManager.InitPauseUI();

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
    float dt = 0.f;

	// ESC 눌렀는지 감지 (토글 방식)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !prevEscPressed)
	{
		isPaused = !isPaused;   // esc 누를 때마다 멈추고 / 다시 시작
		if (isPaused)
			uiManager.PauseWaveTimer();
		else
			uiManager.ResumeWaveTimer();

		prevEscPressed = true;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		prevEscPressed = false;
	}

	// 일시정지 해제 시 타이머 이어서 흐르게 하기
	if (!isPaused && wasPausedBefore)
	{
		std::cout << "일시정지 해제됨 → 타이머 이어서 흐름" << std::endl;
		uiManager.ResumeWaveTimer();  // ?? waveClock 재시작 아님!
	}
	wasPausedBefore = isPaused;

	// 일시정지 상태일 때 UI만 처리
	if (isPaused)
	{
		sf::Vector2f mousePos = window.mapPixelToCoords(
			sf::Mouse::getPosition(window),
			window.getDefaultView()
		);

		bool nowMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool isClick = !prevMousePressed && nowMousePressed;

		if (isClick)
		{
			if (uiManager.IsMouseOverResume(mousePos))
			{
				isPaused = false;
				uiManager.ResumeWaveTimer();  // 여기도 반드시 호출!
			}
			else if (uiManager.IsMouseOverExit(mousePos))
			{
				sceneManager->ChangeScene("TitleScene");
			}
		}

		prevMousePressed = nowMousePressed;
		return;  // 게임 로직은 멈춘 상태
	}

    // ?? 4. 시간 갱신
    dt = clock.restart().asSeconds();

    // ??? 5. 상점이 열려있으면 게임 로직 멈추고 상점 UI만 처리
    if (uiManager.IsShopOpen())
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(
            sf::Mouse::getPosition(window),
            window.getDefaultView()
        );

        bool nowMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        bool isClick = !prevMousePressed && nowMousePressed;

        uiManager.UpdateShop(mousePos, isClick);
        prevMousePressed = nowMousePressed;
        wasShopOpen = true;
        return;
    }

    // ? 6. 상점이 막 닫힌 직후 처리 (현재는 주석)
    if (wasShopOpen && !uiManager.IsShopOpen())
    {
        // 다음 웨이브 시작 로직 필요시 여기에 작성
    }

    // ?? 7. 웨이브 타이머 30초 경과 시 상점 열기 대기
    if (!waveEnded && uiManager.GetWaveElapsedTime() >= 30.f)
    {
        waveEnded = true;
        waveEndTimer = 0.f;
    }

    // ? 8. 웨이브 종료 후 1초 대기 → 상점 오픈
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

    // ?? 9. 일반 게임 로직 처리
    stage->Update(dt);
    uiManager.Update(dt);

    // ?? 10. 상점 상태 기록 갱신
    wasShopOpen = false;
}


void GameScene::Render(sf::RenderWindow& window)
{
	stage->Render(window);
	uiManager.Render(window); // UI 매니저 렌더링
	if (isPaused)
		uiManager.RenderPauseUI(window);

}

void GameScene::ResetGame()
{
	cout << "[리셋됨] GameScene::ResetGame() 호출됨" << endl;

	isResetting = true;  // 리셋 시작

	selectedStatChoices.clear();		// 선택된 스탯 초기화

	delete stage;
	stage = new Stage();
	stage->Init();

	uiManager.Init();
	stage->stageManager->SetUIManager(&uiManager);
	stage->player->uiManager = &uiManager;

	stage->stageManager->SetResetting(true); // 리셋 상태 설정

	stage->stageManager->NextWave(*stage->player, uiManager, -1, {});
	stage->stageManager->SetResetting(false);
	uiManager.ShowWaveText(stage->stageManager->GetCurrentWave());
	uiManager.SetPlayer(stage->player);

	uiManager.ResetWaveTimer();
	uiManager.SetPaused(false);
	uiManager.InitShop(*stage->player->stats);
	clock.restart();

	isPaused = false;
	wasPausedBefore = false;
	prevEscPressed = false;
	waveEnded = false;
	waveEndTimer = 0.f;
	wasShopOpen = false;
	prevMousePressed = false;

	if (stage->player->stats)
		stage->player->stats->Reset();

	stage->player->SetPosition({ 960.f, 540.f });

	Stage::killCount = 0;


	uiManager.shopUI.ClearSelectedChoices();	// 선택된 스탯 초기화
	uiManager.ClearStatLog();
	

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
