#include "GameScene.h"
#include "PlayerStats.h"
#include "SoundManager.h"
#include "TitleScene.h"

// 게임 씬 클래스: 게임의 주된 플레이 로직과 흐름을 담당

GameScene::GameScene()
{
	game = new Game();          // 게임 상태 정보 초기화 (wave, pause 등)
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

// ------------------------------------------
// 게임 시작 시 한 번만 호출되는 초기화 함수
// ------------------------------------------
void GameScene::Init()
{
	game->Reset(); // 전체 게임 상태 초기화

	// 배경 음악 로드 및 재생
	if (soundManager.LoadBGM(GetSoundPath("Stage_BGM_1.wav")))
		soundManager.PlayBGM(true);

	uiManager.Init();        // 일반 UI 초기화
	uiManager.InitPauseUI(); // 일시정지 UI 초기화

	// 스테이지 및 플레이어 생성
	stage = new Stage();
	stage->Init();
	stage->stageManager->SetUIManager(&uiManager);      // UI 연동
	stage->player->uiManager = &uiManager;              // 플레이어에도 UI 연동

	// 첫 번째 웨이브 시작 (선택 없음, 빈 스탯)
	stage->stageManager->NextWave(*stage->player, uiManager, -1, {});
	game->SetWave(stage->stageManager->GetCurrentWave());

	uiManager.ShowWaveText(game->GetWave());    // 웨이브 숫자 표시
	uiManager.SetPlayer(stage->player);         // 플레이어 정보 UI에 연동
	uiManager.ResetWaveTimer();                 // 웨이브 타이머 초기화

	clock.restart(); // 시간 측정용

	// 상점에서 스탯 선택 시 호출될 콜백 함수 등록
	uiManager.shopUI.SetOnSelect([this](int selectedIndex)
		{
			uiManager.shopUI.Close(); // 상점 닫기

			if (selectedIndex != -1)  // 선택했다면
			{
				game->SetSelectedChoices(uiManager.shopUI.GetSelectedChoices());
			}

			// 다음 웨이브 시작
			stage->stageManager->NextWave(*stage->player, uiManager, selectedIndex, game->GetSelectedChoices());
			game->NextWave();                         // 웨이브 수 증가
			uiManager.ShowWaveText(game->GetWave());  // UI 반영
			uiManager.ResetWaveTimer();               // 타이머 재설정
		});
}

// ------------------------------------------
// 프레임마다 실행되는 Update 함수
// ------------------------------------------
void GameScene::Update(sf::RenderWindow& window)
{
	float dt = 0.f;

	// 1. ESC 눌렀는지 감지해서 일시정지 On/Off 처리
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !prevEscPressed)
	{
		game->SetPaused(!game->IsPaused()); // 상태 전환
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

	// 2. 일시정지 상태면, 일시정지 UI만 처리하고 리턴
	if (game->IsPaused())
	{
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getDefaultView());
		bool nowMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);		// 마우스 좌클릭 상태 확인
		bool isClick = !prevMousePressed && nowMousePressed;					// 이전 프레임에 클릭하지 않았고 현재 클릭 상태인 경우

		if (isClick)
		{
			if (uiManager.IsMouseOverResume(mousePos))  // Continue 클릭
			{
				game->SetPaused(false);
				uiManager.ResumeWaveTimer();
			}
			else if (uiManager.IsMouseOverExit(mousePos))  // Exit 클릭
			{
				sceneManager->ChangeScene("Title");
			}
		}

		prevMousePressed = nowMousePressed;
		return;  // 일시정지 상태에서는 게임 로직 중지
	}

	// 3. 시간 갱신
	dt = clock.restart().asSeconds();

	// 4. 상점이 열려있으면 상점 UI만 업데이트
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

	// 5. 상점이 닫힌 직후 (예비 처리)
	if (wasShopOpen && !uiManager.IsShopOpen())
	{
		// 필요한 작업 있으면 추가
	}

	// 6. 웨이브 종료 조건 (30초 이상 지남)
	if (!waveEnded && uiManager.GetWaveElapsedTime() >= 30.f)
	{
		waveEnded = true;
		waveEndTimer = 0.f;
	}

	// 7. 웨이브 종료 후 1초 뒤 상점 오픈
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

	// 8. 메인 게임 로직 업데이트
	stage->Update(dt);
	uiManager.Update(dt);

	// 9. 상점 상태 초기화
	wasShopOpen = false;
}

// ------------------------------------------
// 화면에 게임, UI 렌더링
// ------------------------------------------
void GameScene::Render(sf::RenderWindow& window)
{
	stage->Render(window);            // 스테이지(플레이어/적) 그리기
	uiManager.Render(window);         // 체력바, 경험치, 타이머 등 UI 그리기

	if (game->IsPaused())            // 일시정지 시
		uiManager.RenderPauseUI(window); // 일시정지 메뉴 표시
}

// ------------------------------------------
// 게임 오버 후 재시작 시 상태 초기화
// ------------------------------------------
void GameScene::ResetGame()
{
	cout << "[리셋됨] GameScene::ResetGame() 호출됨" << endl;

	// 게임 상태 및 UI 초기화
	game->Reset();
	uiManager.ClearStatLog();

	// 스테이지 및 플레이어 재생성
	delete stage;
	stage = new Stage();
	stage->Init();
	stage->stageManager->SetUIManager(&uiManager);
	stage->player->uiManager = &uiManager;

	// 초기 스탯 선택 반영 없이 웨이브 시작 (Resetting 처리)
	stage->stageManager->SetResetting(true);		// 이게 없으면 스탯UI가 초기화가 안돼요ㅠㅠ 내부만 리셋되고 외부가 안됨ㅠㅠㅠㅠㅠㅠ
	stage->stageManager->NextWave(*stage->player, uiManager, -1, {});
	stage->stageManager->SetResetting(false);

	// 현재 웨이브를 게임 상태에 저장하고, UI에 표시
	game->SetWave(stage->stageManager->GetCurrentWave());  // 현재 웨이브 정보 저장
	uiManager.ShowWaveText(game->GetWave());               // 웨이브 텍스트 UI 업데이트

	// UIManager에 새로 생성된 플레이어 등록 + 타이머 리셋
	uiManager.SetPlayer(stage->player);
	uiManager.ResetWaveTimer();

	// 일시정지 상태 초기화 및 상점 UI 준비
	uiManager.SetPaused(false);
	uiManager.InitShop(*stage->player->stats);            // 초기 스탯 기준으로 상점 구성
	clock.restart();                                      // 시간 초기화

	// 플레이어 상태 초기화
	stage->player->stats->Reset();                        // 스탯(HP/공속 등) 초기화
	uiManager.UpdateStatusUI();  // ← 경험치 바 포함한 UI 수치 갱신
	stage->player->SetPosition({ 960.f, 540.f });         // 화면 중앙 위치로 이동



	// 상점 UI 선택 기록 초기화
	uiManager.shopUI.ClearSelectedChoices();

	// 상점 선택 콜백 재등록 (다음 웨이브로 넘기기 위한 핵심 로직)
	uiManager.shopUI.SetOnSelect([this](int selectedIndex)
		{
			uiManager.shopUI.Close();  // 상점 닫기

			if (selectedIndex != -1)
			{
				// 선택된 능력치 저장
				game->SetSelectedChoices(uiManager.shopUI.GetSelectedChoices());
			}

			// 선택한 능력 적용 후 다음 웨이브로 진입
			stage->stageManager->NextWave(*stage->player, uiManager, selectedIndex, game->GetSelectedChoices());
			game->NextWave();  // 웨이브 카운터 증가
			uiManager.ShowWaveText(game->GetWave());  // 웨이브 UI 반영
			uiManager.ResetWaveTimer();               // 타이머 리셋
		});
}