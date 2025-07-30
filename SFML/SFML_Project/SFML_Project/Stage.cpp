#include "Stage.h"
#include "Enemy.h"

int Stage::killCount = 0;

void Stage::Init()
{
	map.Load("background.png");

	if (stageManager == nullptr)
	{
		// 효 추가 : StageManager 생성 및 초기화
		stageManager = new StageManager();
		// 효 추가 : Player 객체 생성 및 StageManager에 설정
		player = new Player();
		//player->SetUIManager(uiManager); // Player에 UI 매니저 설정 (2025-07-26 효 추가)
		stageManager->SetPlayer(player);  // StageManager에 Player 설정
		stageManager->Init();  // 적 텍스처 등 초기화
		
	}
	view.setSize(1920.f, 1080.f);//화면으로 보여줄 뷰 크기 
	
}


void Stage::Update(float deltaTime)
{
	
	//추가
	if (stageManager)
	{
		stageManager->Update(deltaTime, player->GetPosition());
		HandlePlayerEnemyCollision();
		auto& bullets = stageManager->GetBullets();
		sf::FloatRect playerBounds = player->GetGlobalBounds();
		//화면 밖으로 나가면 투사체가 사라지도록 하기 위한 화면크기 구하는 코드
		sf::FloatRect viewBounds(
			view.getCenter().x - view.getSize().x / 2.f,
			view.getCenter().y - view.getSize().y / 2.f,
			view.getSize().x,
			view.getSize().y
		);


		for (int i = bullets.size() - 1; i >= 0; --i)
		{
			sf::FloatRect bulletBounds = bullets[i].sprite.getGlobalBounds();
			if (playerBounds.intersects(bullets[i].sprite.getGlobalBounds()))
			{
				std::cout << "투사체 충돌! damage: " << bullets[i].damage << std::endl;
				player->TakeDamage(bullets[i].damage); //직접 저장된 데미지를 사용
				bullets.erase(bullets.begin() + i);    //투사체 제거
			}
			//투사체 화면나감
			else if (!viewBounds.intersects(bulletBounds))
			{
				bullets.erase(bullets.begin() + i);
				//cout << "적투사체 화면밖으로 나감" << endl;
				continue;
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
			

			enemy->TakeDamage(player->stats->damage);   // 플레이어가 가하는 피해
			
			//나중에 무기에 넣을거면 재횔용될듯

			if (enemy->IsDead())
			{
				Stage::killCount++; // 적 처치 수 증가
				player->GainExperience();
				delete enemy;
				enemies.erase(enemies.begin() + i);
			}
		}
	}
}
