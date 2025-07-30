#include "TitleScene.h"
#include "SoundManager.h"
#include "GameScene.h"

// 생성자: 각종 멤버 변수 기본값 초기화
TitleScene::TitleScene()
{
    scaleDirection = 1.0f;
    scaleSpeed = 0.5f;
    minScale = 0.9f;
    maxScale = 1.1f;
    textAnimTimer = 0.f;

    backgroundX1 = 0.f;
    backgroundX2 = 0.f;
    backgroundScrollSpeed = 15.f;

    canStart = true;
    enterPreviouslyPressed = false;
}

// Init: 리소스 로딩, 텍스트 및 배경 설정
void TitleScene::Init()
{
    // 배경음악 로딩 및 재생
    if (soundManager.LoadBGM(GetSoundPath("Main_Display_BGM.wav")))
    {
        soundManager.PlayBGM(true);  // 반복 재생
    }

    // 배경 이미지 로드
    if (!backgroundTexture.loadFromFile(GetrscPath("BackGround7.png")))
    {
        cerr << "배경 이미지 로드 실패!" << endl;
    }

    // 스프라이트 텍스처 설정
    backgroundSprite1.setTexture(backgroundTexture);
    backgroundSprite2.setTexture(backgroundTexture);

    // 해상도에 맞게 스케일 계산
    sf::Vector2u windowSize = { 1920, 1080 };
    sf::Vector2u textureSize = backgroundTexture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    backgroundSprite1.setScale(scaleX, scaleY);
    backgroundSprite2.setScale(scaleX, scaleY);

    // 배경 위치 초기화
    backgroundX1 = 0.f;
    backgroundX2 = static_cast<float>(textureSize.x) * scaleX;

    backgroundSprite1.setPosition(backgroundX1, 0.f);
    backgroundSprite2.setPosition(backgroundX2, 0.f);

    // 폰트 로드
    font.loadFromFile(GetrscPath("Font/BMJUA_ttf.ttf"));

    // 타이틀 텍스트 설정
    titleText.setFont(font);
    titleText.setString("Meowbellion");
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::Black);

    // 텍스트 중앙 정렬
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
    titleText.setPosition(1920.f / 2.f, 1080.f / 2.f - 30.f);  // 중앙에서 위로 살짝

    // 시작 안내 텍스트 설정
    startText.setFont(font);
    startText.setString("<Press Enter to Start>");
    startText.setCharacterSize(50);
    startText.setFillColor(sf::Color::Black);

    // 시작 텍스트 중앙 정렬
    sf::FloatRect startBounds = startText.getLocalBounds();
    startText.setOrigin(startBounds.left + startBounds.width / 2.0f, startBounds.top + startBounds.height / 2.0f);
    startText.setPosition(1920.f / 2.f, 1080.f / 2.f + 60.f);  // 중앙에서 아래로 살짝
}

// Update: 애니메이션 및 입력 처리
void TitleScene::Update(sf::RenderWindow& window)
{
    float deltaTime = clock.restart().asSeconds();

    // 타이틀 텍스트 크기 애니메이션 (살짝 커졌다 작아졌다 반복)
    textAnimTimer += deltaTime;
    float scale = 1.0f + 0.1f * sin(textAnimTimer * 2.f);
    titleText.setScale(scale, scale);

    // 배경 스크롤
    float scaledWidth = backgroundTexture.getSize().x * backgroundSprite1.getScale().x;
    backgroundX1 -= backgroundScrollSpeed * deltaTime;
    backgroundX2 -= backgroundScrollSpeed * deltaTime;

    // 스크롤 되면 반대편으로 재배치
    if (backgroundX1 + scaledWidth < 0)
        backgroundX1 = backgroundX2 + scaledWidth;
    if (backgroundX2 + scaledWidth < 0)
        backgroundX2 = backgroundX1 + scaledWidth;

    backgroundSprite1.setPosition(backgroundX1, 0.f);
    backgroundSprite2.setPosition(backgroundX2, 0.f);

    // 엔터 키 입력 시 게임 시작
    bool enterNowPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
    if (!enterPreviouslyPressed && enterNowPressed)
    {
        soundManager.StopBGM();  // 타이틀 BGM 종료

        // GameScene 초기화
        GameScene* gameScene = dynamic_cast<GameScene*>(SceneManager::GetScene("Game"));
        if (gameScene)
        {
            cout << "[디버그] ResetGame 호출 시도" << endl;
            gameScene->ResetGame();  // 게임 상태 초기화
        }

        // 씬 전환
        SceneManager::ChangeScene("Game");
    }
    enterPreviouslyPressed = enterNowPressed;

    // ESC 입력 시 창 닫기
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
    }
}

// Render: 화면 출력
void TitleScene::Render(sf::RenderWindow& window)
{
    // 기본 뷰 설정
    window.setView(window.getDefaultView());

    // 배경 → 텍스트 순서대로 렌더링
    window.draw(backgroundSprite1);
    window.draw(backgroundSprite2);
    window.draw(titleText);
    window.draw(startText);
}
