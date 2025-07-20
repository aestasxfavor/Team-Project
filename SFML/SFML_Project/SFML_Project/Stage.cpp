//#include "Stage.h"
//
//void Stage::Init()
//{
//	if (player == nullptr)
//	{
//		player = new Player;
//	}
//	map.Load("background.png");
//	player->Init();
//
//	// charTex.loadFromFile(GetrscPath("player_cat.png"));
//	// SPplayer.setTexture(charTex);
//	// SPplayer.setTextureRect(sf::IntRect(0,40, 48, 48));
//
//
//
//	// sfml include 해서 세팅하거나 
//	// 그냥 초기화 진행 할거
//
//	//추가
//	view.setSize(800.f, 600.f);//화면으로 보여줄 뷰 크기 
//
//}
//
//void Stage::Update(float deltaTime)
//{
//
//	player->Update(deltaTime);
//	// enemyManager.update();
//	// dropManager.update();
//	// uiManager.update();
//	// effectManager.update();
//	//추가
//	view.setCenter(player->GetPosition());
//}
//	
//void Stage::Render(sf::RenderWindow& window)
//{
//	//map.Render(window);
//	//player->Render(window);
//	// sfml include 해서 draw해야할 것들
//	//추가
//	window.setView(view);// 카메라시야를 플레이어따라
//	map.Render(window, player->GetPosition());
//	player->Render(window); 
//}
