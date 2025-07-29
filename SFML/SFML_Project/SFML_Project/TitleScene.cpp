#include "TitleScene.h"

void TitleScene::Init()
{
 
        if (!backgroundTexture.loadFromFile(GetrscPath("BackGround7.png")))
        {
            std::cerr << "배경 이미지 로드 실패!" << std::endl;
        }

        // 텍스처 설정
        backgroundSprite1.setTexture(backgroundTexture);
        backgroundSprite2.setTexture(backgroundTexture);

        // ?? 여기서 윈도우 사이즈에 맞춰 스케일 조절!
        sf::Vector2u windowSize = {1920, 1080 };  // 고정된 창 사이즈   1920x1080으로 전체 사이즈 수정하기    10시간 뒤의 효가 수정하겠지ㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠ
        sf::Vector2u textureSize = backgroundTexture.getSize();

        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

        backgroundSprite1.setScale(scaleX, scaleY);
        backgroundSprite2.setScale(scaleX, scaleY);

        // 위치 조정
        backgroundX1 = 0.f;
        backgroundX2 = static_cast<float>(backgroundTexture.getSize().x) * scaleX;

        backgroundSprite1.setPosition(backgroundX1, 0.f);
        backgroundSprite2.setPosition(backgroundX2, 0.f);

        // 폰트 & 텍스트
        font.loadFromFile(GetrscPath("Font/BMJUA_ttf.ttf"));

  //      titleText.setFont(font);
  //      titleText.setString("Meowbellion");
  //      titleText.setCharacterSize(60);
  //      titleText.setFillColor(sf::Color::Black);
  //      titleText.setPosition(1920.f/2.f, 1080.f/2.f);

  //      startText.setFont(font);
  //      startText.setString("<Press Enter to Start>");
		////startText.setString(L"엔터키.");       // 한글 쓰는 방법 : L"문자열"
  //      startText.setCharacterSize(30);
  //      startText.setFillColor(sf::Color::Black);
  //      startText.setPosition(1920.f/2.f, 1080.f/2.f);

        // 제목 텍스트 (중앙 정렬)
        titleText.setFont(font);
        titleText.setString("Meowbellion");
        titleText.setCharacterSize(80);
        titleText.setFillColor(sf::Color::Black);

        // 텍스트의 바운딩 박스를 기준으로 중심점을 origin으로 설정
        sf::FloatRect titleBounds = titleText.getLocalBounds();
        titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
        titleText.setPosition(1920.f / 2.f, 1080.f / 2.f - 30.f);  // 살짝 위로

        // 시작 텍스트 (중앙 정렬)
        startText.setFont(font);
        startText.setString("<Press Enter to Start>");
        startText.setCharacterSize(50);
        startText.setFillColor(sf::Color::Black);

        // origin 설정
        sf::FloatRect startBounds = startText.getLocalBounds();
        startText.setOrigin(startBounds.left + startBounds.width / 2.0f, startBounds.top + startBounds.height / 2.0f);
        startText.setPosition(1920.f / 2.f, 1080.f / 2.f + 60.f);  // 살짝 아래로

    
}

void TitleScene::Update(sf::RenderWindow& window)       // 2025-07-28 13:20 효 추가 :  여기 손봐야겠네 
{
    float deltaTime = clock.restart().asSeconds();

    // 텍스트 크기 애니메이션
    textAnimTimer += deltaTime;
    float scale = 1.0f + 0.1f * std::sin(textAnimTimer * 2.f);
    titleText.setScale(scale, scale);

    //  스케일 적용된 배경 너비 계산
    float scaledWidth = backgroundTexture.getSize().x * backgroundSprite1.getScale().x;

    // 배경 스크롤
    backgroundX1 -= backgroundScrollSpeed * deltaTime;
    backgroundX2 -= backgroundScrollSpeed * deltaTime;

    if (backgroundX1 + scaledWidth < 0)
        backgroundX1 = backgroundX2 + scaledWidth;
    if (backgroundX2 + scaledWidth < 0)
        backgroundX2 = backgroundX1 + scaledWidth;

    backgroundSprite1.setPosition(backgroundX1, 0.f);
    backgroundSprite2.setPosition(backgroundX2, 0.f);

    // 입력 처리
    if (canStart && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        canStart = false;
        SceneManager::ChangeScene("Game");
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
    }
}

void TitleScene::Render(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());

    window.draw(backgroundSprite1);
    window.draw(backgroundSprite2);
    window.draw(titleText);
    window.draw(startText);
}