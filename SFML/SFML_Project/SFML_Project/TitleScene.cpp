#include "TitleScene.h"

void TitleScene::Init() {

    if (!backgroundTexture.loadFromFile(GetrscPath("background.png"))) {
        std::cerr << "배경 이미지 로드 실패!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0);  // 화면 왼쪽 위 시작


    font.loadFromFile(GetrscPath("Font/BMJUA_ttf.ttf"));

    titleText.setFont(font);
    titleText.setString("Meowbellion");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(300, 200);

    startText.setFont(font);
    startText.setString("Press Enter to Start");
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(320, 350);

   

}

void TitleScene::Update(sf::RenderWindow& window)
{
    if (canStart && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) 
    {
        canStart = false;
        SceneManager::ChangeScene("Game"); // Game 씬 이름으로 등록되어 있어야 함
    }


}

void TitleScene::Render(sf::RenderWindow& window)
{
        window.draw(backgroundSprite);  // 배경 먼저 그리기
        window.draw(titleText);
        window.draw(startText);
}
