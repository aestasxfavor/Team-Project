#include "StageManager.h"


StageManager::StageManager() 
{
    spawnInterval = 1.0f;    // 적 생성 간격을 5초로 설정
    spawnTimer = 0.f;       // 생성 타이머 초기화
    player = nullptr;
}

StageManager::~StageManager() 
{
    Clear();                // 소멸자에서 적들 메모리 정리
}

void StageManager::Init() 
{
  
	player->Init(); // 효 추가 : 플레이어 초기화
    //enemyTexture.loadFromFile("enemy.png");  // 적 텍스처 파일 로드
    //추가
    //테스트용 슬라임 이미지
    slimeTexture.loadFromFile(GetrscPath("slime.png"));
    spriteSlime.setTexture(texture);    // 효 추가 : [확인 필요] texture 변수는 slimeTexture와 역할이 겹치는 것 같음 의도가 불분명.. 상의 후 결정하기
    spriteSlime.setPosition(370.f, 280.f);
    //spriteSlime.setTextureRect(sf::IntRect(0, 227, 227 , 227));'
    
    //enemy01이미지
    std::string path = GetrscPath("enemy01.png");
    if (!enemy01Texture.loadFromFile(path))
    {
        std::cout << "enemy01.png 로딩 실패!" << std::endl;
        std::cout << "시도된 경로: " << path << std::endl;
    }
}

void StageManager::Update(float dt, sf::Vector2f playerPos) 
{
	player->Update(dt); // 효 추가 : 플레이어 업데이트
    spawnTimer += dt;       // 누적된 시간 갱신

    if (spawnTimer >= spawnInterval && enemies.size()< maxEnemies)   // 생성 간격이 지나면
    {
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


void StageManager::SpawnEnemy(sf::Vector2f playerPos)
{
    float angle = static_cast<float>(rand() % 360) * 3.1415926f / 180.f;
    float distance = minSpawnDistance + static_cast<float>(rand()) / RAND_MAX * 300.f;

    sf::Vector2f spawnPos =
    {
        playerPos.x + cos(angle) * distance,
        playerPos.y + sin(angle) * distance
    };

    Enemy* enemy = nullptr;

    int enemyType = rand() % 2;  // 현재는 2종 (0: slime, 1: enemy01)   // 2025-07-22 14:14분 효 추가 : enum으로 설계해도 될거 같음 일단 보류하기 

    switch (enemyType)
    {
    case 0:
        enemy = new slime(slimeTexture, spawnPos);
        break;
    case 1:
        enemy = new enemy01(texture, spawnPos);
        break;
    default:
        enemy = new slime(slimeTexture, spawnPos); // 기본값
        break;
    }

    enemies.push_back(enemy);
}

void StageManager::Draw(sf::RenderWindow& window) 
{
	player->Render(window); // 효 추가 : 플레이어 렌더링

    for (auto& enemy : enemies) 
    {
        enemy->Draw(window);        // 각 적을 화면에 그림
    }
}

void StageManager::Clear() 
{
    for (auto enemy : enemies) 
    {
        delete enemy;               // 모든 적 메모리 해제
    }
    enemies.clear();                // 리스트 비우기
}

vector<Enemy*>& StageManager::GetEnemies()
{
    return enemies;
}

Player* StageManager::GetPlayer()
{
    return player;
}

void StageManager::SetPlayer(Player* _player)
{
    player = _player; 
}

