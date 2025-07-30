#include "GameOverScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "SoundManager.h"

extern SceneManager sceneManager;

void GameOverScene::Init()
{
    animatedTextLetters.clear();

    cout << "[GameOverScene] Init 호출됨" << endl;

    if (!backgroundTexture.loadFromFile(GetrscPath("background.png")))
    {
        cerr << "GameOverScene 배경 이미지 로드 실패!" << endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // 🔹 해상도에 맞춰 배경 스케일 조정
    sf::Vector2u windowSize = { 1920, 1080 };
    sf::Vector2u textureSize = backgroundTexture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    backgroundSprite.setScale(scaleX, scaleY);
    backgroundSprite.setPosition(0.f, 0.f); // 좌측 상단 고정

    // 🔹 폰트 로드
    if (!font.loadFromFile(GetrscPath("Font/BMJUA_ttf.ttf")))
    {
        cerr << "폰트 로딩 실패!" << endl;
    }

    string textStr = "Game Over";
    float letterSpacing = 60.f; // 글자 간격
    float startX = 1920.f / 2.f - (textStr.size() / 2.f * letterSpacing);
    float baseY = 1080.f / 2.f - 150.f;

    for (size_t i = 0; i < textStr.size(); i++)
    {
        sf::Text letter;
        letter.setFont(font);
        letter.setString(textStr[i]);
        letter.setCharacterSize(100);         // 더 크게 보여도 괜찮을 듯
        letter.setFillColor(sf::Color::White);
        letter.setPosition(startX + i * letterSpacing, baseY);
        animatedTextLetters.push_back(letter);
    }

    // 🔹 Press Enter 텍스트
    restartText.setFont(font);
    restartText.setString("Press Enter to Title");
    restartText.setCharacterSize(50);
    restartText.setFillColor(sf::Color::White);

    sf::FloatRect reBounds = restartText.getLocalBounds();
    restartText.setOrigin(reBounds.left + reBounds.width / 2.f, reBounds.top + reBounds.height / 2.f);
    restartText.setPosition(1920.f / 2.f, 1080.f / 2.f + 60.f);
}

void GameOverScene::Update(sf::RenderWindow& window)
{
 
    float dt = clock.restart().asSeconds();  
    animationTimer += dt * 2.f;  // ← 여기서 2.f를 줄이면 느려짐, 늘리면 빨라짐

    for (size_t i = 0; i < animatedTextLetters.size(); i++)
    {
        float offset = sin(animationTimer + i * 0.3f); // 순차적 애니메이션
        float y = 1080.f / 2.f - 150.f;
        animatedTextLetters[i].setPosition(animatedTextLetters[i].getPosition().x, y);

        // 깜빡이는 느낌 줄 거면 알파값 조정
        int alpha = static_cast<int>(128 + 127 * sin(animationTimer + i * 0.3f));
        animatedTextLetters[i].setFillColor(sf::Color(255, 255, 255, alpha));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        GameScene* gameScene = dynamic_cast<GameScene*>(SceneManager::GetScene("Game"));
        if (gameScene)
        {
            gameScene->ResetGame();  // 상태 초기화
        }
		    soundManager.StopBGM();  // 브금 멈추기
            SceneManager::ChangeScene("Title");
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
    }
}

void GameOverScene::Render(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());  // 카메라 초기화 (중앙 고정)

    window.clear(sf::Color::Black);
    window.draw(backgroundSprite);
 
    // Render()에서 기존 gameOverText 대신
    for (auto& letter : animatedTextLetters)
    {
        window.draw(letter);
    }
    window.draw(restartText);
}

