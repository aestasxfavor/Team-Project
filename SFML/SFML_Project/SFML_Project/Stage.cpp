#include "Stage.h"

void Stage::Init()
{
	map.Load("background.png");

	if (stageManager == nullptr)
	{
		// 효 추가 : StageManager 생성 및 초기화
		stageManager = new StageManager();
		// 효 추가 : Player 객체 생성 및 StageManager에 설정
		player = new Player();
		stageManager->SetPlayer(player);  // StageManager에 Player 설정
		stageManager->Init();  // 적 텍스처 등 초기화
		
	}

	// charTex.loadFromFile(GetrscPath("player_cat.png"));
	// SPplayer.setTexture(charTex);
	// SPplayer.setTextureRect(sf::IntRect(0,40, 48, 48));



	// sfml include 해서 세팅하거나 
	// 그냥 초기화 진행 할거

	//추가
	view.setSize(800.f, 600.f);//화면으로 보여줄 뷰 크기 
	
}

void Stage::Update(float deltaTime)
{
	// enemyManager.update();
	// dropManager.update();
	// uiManager.update();
	// effectManager.update();
	//추가
	if (stageManager)
	{
		stageManager->Update(deltaTime, player->GetPosition());
		HandlePlayerEnemyCollision();
		auto& bullets = enemyManager->GetBullets();
		sf::FloatRect playerBounds = player->GetGlobalBounds();

		for (int i = bullets.size() - 1; i >= 0; --i)
		{

			if (playerBounds.intersects(bullets[i].sprite.getGlobalBounds()))
			{
				std::cout << "투사체 충돌! damage: " << bullets[i].damage << std::endl;
				player->TakeDamage(bullets[i].damage); //직접 저장된 데미지를 사용
				bullets.erase(bullets.begin() + i);    //투사체 제거
			}
		}
	}
	view.setCenter(player->GetPosition());
}
	
void Stage::Render(sf::RenderWindow& window)
{
	//map.Render(window);
	//player->Render(window);
	// sfml include 해서 draw해야할 것들
	//추가
	window.setView(view);// 카메라시야를 플레이어따라
	map.Render(window, player->GetPosition());
	player->Render(window); 
	if (stageManager) stageManager->Draw(window);
}

void Stage::HandlePlayerEnemyCollision()//충돌관련 (2025-07-21 준호님 추가)
{
	sf::FloatRect playerBounds = player->GetGlobalBounds();
	auto& enemies = stageManager->GetEnemies();  

	for (int i = enemies.size() - 1; i >= 0; --i)
	{
		Enemy* enemy = enemies[i];
		sf::FloatRect enemyBounds = enemy->GetGlobalBounds();

		if (playerBounds.intersects(enemyBounds))
		{
			player->TakeDamage(enemy->GetAtk());   // 플레이어가 받는 피해
			//나중에 에너미 atk로 수정
			enemy->TakeDamage(999);   // 플레이어가 가하는 피해
			//테스트용이라 999로 설정했습니다.
			//나중에 무기에 넣을거면 재횔용될듯

			if (enemy->IsDead())
			{
				killCount++;
				delete enemy;
				enemies.erase(enemies.begin() + i);
				std::cout << "Kill Count: " << killCount << std::endl;
			}
		}
	}
}
