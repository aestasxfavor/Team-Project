#include "Stage.h"
#include "Util.h"
#include "StageManager.h"
#include "SceneManager.h"
#include"Enemy.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

    Stage stage;
    stage.Init();

    sf::Clock clock;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // deltaTime 계산 (선택)
        float dt = clock.restart().asSeconds();

        // 게임 로직 업데이트
        stage.Update(dt);

        // 화면 그리기
        window.clear();

        stage.Render(window);  // 여기서 SFML로 그리려면 Stage/Player/Enemy들이 SFML의 draw를 이용해야 함.

        window.display();
    }

    return 0;
}