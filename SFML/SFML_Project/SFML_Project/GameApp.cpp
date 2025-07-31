#include "GameApp.h"

// 씬을 2개이상을 사용해서 넘기는 구조로 사용하지 않고 하나의 씬을 사용해서 이어지도록 구현 (씬 관리)


// 씬 2개 안씀 하나로 이어서 씀;;;;;;;;;;;;

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
    if (window.isOpen())
        window.close();
	// 씬 매니저의 모든 씬을 삭제

	cout << "[GameApp] 소멸자 호출됨" << endl;
}

void GameApp::Init()
{
    // 창 생성
    window.create(sf::VideoMode(1920, 1080), "Meowbellion");

    // 씬 등록
    SceneManager::AddScene("Title", new TitleScene());
    SceneManager::AddScene("Game", new GameScene());
    SceneManager::AddScene("GameOver", new GameOverScene());

    // 시작 씬 설정
    SceneManager::ChangeScene("Title");
}

// 메인 루프
// - 창이 열려 있는 동안 이벤트 처리 + 게임 씬 업데이트/렌더링 반복
void GameApp::Run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        SceneManager::Update(window);

        window.clear();
        SceneManager::Render(window);
        window.display();
    }
}
