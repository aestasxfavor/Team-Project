//#include "Stage.h"
//#include "Util.h"
//#include "StageManager.h"
//#include "SceneManager.h"
//#include "TitleScene.h"
//#include "GameScene.h"
//#include"Enemy.h"
//#include "GameOverScene.h"
//
//int main()
//{
//    // 2025-07-29 01:32분 커밋하기위한 효의 주석
//    
//        sf::RenderWindow window(sf::VideoMode(1920, 1080), "Meowbellion");
//
//        SceneManager::AddScene("Title", new TitleScene());
//        SceneManager::AddScene("Game", new GameScene());
//        SceneManager::AddScene("GameOver", new GameOverScene()); //  등록
//        SceneManager::AddScene("TitleScene", new TitleScene());
//        SceneManager::ChangeScene("Title");
//
//        sf::Clock clock;
//
//        while (window.isOpen()) 
//        {
//            sf::Event event;
//            while (window.pollEvent(event)) 
//            {
//                if (event.type == sf::Event::Closed)
//                    window.close();
//            }
//
//            SceneManager::Update(window);
//
//            window.clear();
//            SceneManager::Render(window);
//            window.display();
//        }
//
//        return 0;
//    }
//
//
//    ////sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
//
//  
//
//    //sf::RenderWindow window(sf::VideoMode(800, 600), "Meowbellion");
//
//    //// 씬 등록
//    //SceneManager::AddScene("Title", new TitleScene());
//    //SceneManager::AddScene("Game", new GameScene()); //← GameScene 준비되면 추가
//    //SceneManager::ChangeScene("Title");
//
//    //Stage stage;
//    //stage.Init();
//
//    //sf::Clock clock;
//    //while (window.isOpen())
//    //{
//
//    //    sf::Event event;
//    //    while (window.pollEvent(event))
//    //    {
//    //        if (event.type == sf::Event::Closed)
//    //            window.close();
//    //    }
//
//    //    // deltaTime 계산 (선택)
//    //    float dt = clock.restart().asSeconds();
//
//    //    // 게임 로직 업데이트
//    //    stage.Update(dt);
//
//    //    // 화면 그리기
//    //    window.clear();
//
//    //    stage.Render(window);  // 여기서 SFML로 그리려면 Stage/Player/Enemy들이 SFML의 draw를 이용해야 함.
//
//    //    window.display();
//    //}
//
//

#include "GameApp.h"

int main()
{
    GameApp app;
    app.Init();
    app.Run();
    return 0;
}

