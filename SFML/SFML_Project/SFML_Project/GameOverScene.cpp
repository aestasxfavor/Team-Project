#include "GameOverScene.h"
#include "SceneManager.h"

void GameOverScene::Init()
{
    std::cout << "[GameOverScene] Init 호출됨" << std::endl;

    if (!backgroundTexture.loadFromFile(GetrscPath("background.png")))
    {
        std::cerr << "GameOverScene 배경 이미지 로드 실패!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!font.loadFromFile(GetrscPath("Font/BMJUA_ttf.ttf")))
    {
        std::cerr << "폰트 로딩 실패!" << std::endl;
    }
    //font.loadFromFile(GetrscPath("Font/BMJUA_ttf.ttf"));

    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(300, 200);

    restartText.setFont(font);
    restartText.setString("Press Enter to Title");  //  안내 문구 수정
    restartText.setCharacterSize(36);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(300, 300);

    //sf::View defaultView;
    //defaultView.setSize(800, 600);            // 너희 창 사이즈로
    //defaultView.setCenter(800 / 2, 600 / 2);  // 가운데 정렬
    //window.setView(defaultView);   // 또는 window.setView(...) 방식으로
}

void GameOverScene::Update(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) 
    {
        SceneManager::ChangeScene("Game"); // 다시 시작
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) 
    {
        SceneManager::ChangeScene("Title"); //  타이틀 화면으로 전환!
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close(); // 게임 종료
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
    {
        window.close(); // 게임 종료
    }
}

void GameOverScene::Render(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());
    window.clear(sf::Color::Black); // 또는 배경색

    // 배경 이미지가 있다면
    window.draw(backgroundSprite);

    // 텍스트들 그리기
    window.draw(gameOverText);
    window.draw(restartText);

}
