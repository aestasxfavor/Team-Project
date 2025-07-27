#include "TitleScene.h"

void TitleScene::Init()
{
    /*if (!backgroundTexture.loadFromFile(GetrscPath("BackGround2.png")))
    {
        std::cerr << "배경 이미지 로드 실패!" << std::endl;
    }

    backgroundSprite1.setTexture(backgroundTexture);
    backgroundSprite2.setTexture(backgroundTexture);

    backgroundX1 = 0.f;
    backgroundX2 = static_cast<float>(backgroundTexture.getSize().x);

    backgroundSprite1.setPosition(backgroundX1, -100.f);
    backgroundSprite2.setPosition(backgroundX2, -100.f);

    font.loadFromFile(GetrscPath("Font/BMJUA_ttf.ttf"));

    titleText.setFont(font);
    titleText.setString("Meowbellion");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(250, 200);

    startText.setFont(font);
    startText.setString("<Press Enter to Start>");
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(250, 300);*/

 
        if (!backgroundTexture.loadFromFile(GetrscPath("BackGround7.png")))
        {
            std::cerr << "배경 이미지 로드 실패!" << std::endl;
        }

        // 텍스처 설정
        backgroundSprite1.setTexture(backgroundTexture);
        backgroundSprite2.setTexture(backgroundTexture);

        // ?? 여기서 윈도우 사이즈에 맞춰 스케일 조절!
        sf::Vector2u windowSize = { 800, 600 };  // 고정된 창 사이즈
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

        titleText.setFont(font);
        titleText.setString("Meowbellion");
        titleText.setCharacterSize(60);
        titleText.setFillColor(sf::Color::Black);
        titleText.setPosition(250, 200);

        startText.setFont(font);
        startText.setString("<Press Enter to Start>");
		//startText.setString(L"엔터키.");       // 한글 쓰는 방법 : L"문자열"
        startText.setCharacterSize(30);
        startText.setFillColor(sf::Color::Black);
        startText.setPosition(250, 300);
    
}

void TitleScene::Update(sf::RenderWindow& window)
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