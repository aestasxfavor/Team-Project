#include "EnemyManager.h"


EnemyManager::EnemyManager() 
{
    spawnInterval = 1.0f;    // 적 생성 간격을 5초로 설정
    spawnTimer = 0.f;       // 생성 타이머 초기화
}

EnemyManager::~EnemyManager() 
{
    Clear();                // 소멸자에서 적들 메모리 정리
}

void EnemyManager::Init() 
{
    enemyTexture.loadFromFile("enemy.png");  // 적 텍스처 파일 로드
    //추가
    slimeTexture.loadFromFile(GetrscPath("slime.png"));
    spriteSlime.setTexture(texture);
    spriteSlime.setPosition(370.f, 280.f);
    //spriteSlime.setTextureRect(sf::IntRect(0, 227, 227 , 227));
}

void EnemyManager::Update(float dt, sf::Vector2f playerPos) 
{
    spawnTimer += dt;       // 누적된 시간 갱신

    if (spawnTimer >= spawnInterval && enemies.size()< maxEnemies)   // 생성 간격이 지나면
    {
       // sf::Vector2f spawnPos(rand() % 800, rand() % 600);  // 랜덤 위치 생성
        SpawnEnemy(playerPos);    // 새로운 적 생성 유저를 기준으로 떨어지게 생성
        spawnTimer = 0.f;        // 타이머 초기화
    }

    // 역순으로 적 리스트 순회 (삭제 안정성 확보)
    for (int i = enemies.size() - 1; i >= 0; --i) 
    {
        enemies[i]->Update(dt, playerPos);  // 적 개별 업데이트

        if (enemies[i]->IsDead()) 
        {         // 적이 죽었으면
            delete enemies[i];               // 메모리 해제
            enemies.erase(enemies.begin() + i);  // 리스트에서 제거
        }
    }
}

void EnemyManager::SpawnEnemy(sf::Vector2f playerPos)
{
    float angle = static_cast<float>(rand() % 360) * 3.1415926f / 180.f;
    float distance = minSpawnDistance + static_cast<float>(rand()) / RAND_MAX * 300.f;

    sf::Vector2f spawnPos = 
    {
        playerPos.x + cos(angle) * distance,
        playerPos.y + sin(angle) * distance
    };

    Enemy* newSlime = new slime(slimeTexture, spawnPos);
    enemies.push_back(newSlime);
}

void EnemyManager::Draw(sf::RenderWindow& window) 
{
    for (auto& enemy : enemies) 
    {
        enemy->Draw(window);        // 각 적을 화면에 그림
    }
}

void EnemyManager::Clear() 
{
    for (auto enemy : enemies) 
    {
        delete enemy;               // 모든 적 메모리 해제
    }
    enemies.clear();                // 리스트 비우기
}

