#include "Util.h"
#include "EnemyManager.h"

#pragma region 동민님 코드같음
//#include "Stage1Enemy.hpp"          // 일단 보류
//
//
//// 적 상태 업데이트, 이동 등 처리
//void EnemyManager::update(float dt)
//{
//    for (auto& enemy : enemies) 
//    {
//        enemy->update(dt);
//
//        // 예: 플레이어와 충돌 시 카메라 흔들기
//        if (enemy->sprite.getGlobalBounds().intersects(player->getBounds())) 
//        {
//            camera->shake(2.f);
//            // 추가 데미지 처리 등 가능
//        }
//    }
//
//    // 죽은 적 제거
//    enemies.erase(
//        remove_if(enemies.begin(), enemies.end(),
//            [](const unique_ptr<Enemy>& e) 
//            {
//                return e->isDead();
//            }),
//        enemies.end());
//}
//
//// 적 그리기
//void EnemyManager::draw(sf::RenderTarget& target) const
//{
//    for (const auto& enemy : enemies) 
//    {
//        target.draw(enemy->sprite);
//    }
//}
//
//// 웨이브별 적 생성
//void EnemyManager::spawnWave()
//{
//    static mt19937 rng(random_device{}());
//    static uniform_int_distribution<> dist(0, 1);
//
//    unsigned spawnCount = 5;  // 예시 웨이브 크기
//
//    for (unsigned i = 0; i < spawnCount; i++) 
//    {
//        unique_ptr<Enemy> enemy;
//
//        if (dist(rng) == 0) 
//        {
//            enemy = make_unique<Stage1Enemy>();
//            // 적 텍스처 설정 등 추가
//        }
//        else 
//        {
//            // 만약 Stage2Enemy 등이 있다면 여기에 생성
//            enemy = make_unique<Stage1Enemy>();  // 임시 동일 타입
//        }
//
//        // 적 초기 위치 설정 (예: 맵 랜덤 위치)
//        enemy->sprite.setPosition(100.f * i, 100.f); // 임시 위치
//
//        enemies.push_back(move(enemy));
//    }
//}
#pragma endregion


#pragma region 준호님 코드
EnemyManager::EnemyManager() {
    spawnInterval = 1.0f;    // �� ���� ������ 5�ʷ� ����
    spawnTimer = 0.f;       // ���� Ÿ�̸� �ʱ�ȭ
}

EnemyManager::~EnemyManager() {
    Clear();                // �Ҹ��ڿ��� ���� �޸� ����
}

void EnemyManager::Init() {
    enemyTexture.loadFromFile("enemy.png");  // �� �ؽ�ó ���� �ε�
    //�߰�
    slimeTexture.loadFromFile(GetrscPath("slime.png"));
    spriteSlime.setTexture(texture);
    spriteSlime.setPosition(370.f, 280.f);
    //spriteSlime.setTextureRect(sf::IntRect(0, 227, 227 , 227));
}

void EnemyManager::Update(float dt, sf::Vector2f playerPos) {
    spawnTimer += dt;       // ������ �ð� ����

    if (spawnTimer >= spawnInterval && enemies.size() < maxEnemies)   // ���� ������ ������
    {
        // sf::Vector2f spawnPos(rand() % 800, rand() % 600);  // ���� ��ġ ����
        SpawnEnemy(playerPos);    // ���ο� �� ���� ������ �������� �������� ����
        spawnTimer = 0.f;        // Ÿ�̸� �ʱ�ȭ
    }

    // �������� �� ����Ʈ ��ȸ (���� ������ Ȯ��)
    for (int i = enemies.size() - 1; i >= 0; --i) {
        enemies[i]->Update(dt, playerPos);  // �� ���� ������Ʈ

        if (enemies[i]->IsDead()) {         // ���� �׾�����
            delete enemies[i];               // �޸� ����
            enemies.erase(enemies.begin() + i);  // ����Ʈ���� ����
        }
    }
}

void EnemyManager::SpawnEnemy(sf::Vector2f playerPos)
{
    float angle = static_cast<float>(rand() % 360) * 3.1415926f / 180.f;
    float distance = minSpawnDistance + static_cast<float>(rand()) / RAND_MAX * 300.f;

    sf::Vector2f spawnPos = {
        playerPos.x + cos(angle) * distance,
        playerPos.y + sin(angle) * distance
    };

    Enemy* newSlime = new slime(slimeTexture, spawnPos);
    enemies.push_back(newSlime);
}

void EnemyManager::Draw(sf::RenderWindow& window)
{
    for (auto& enemy : enemies) {
        enemy->Draw(window);        // �� ���� ȭ�鿡 �׸�
    }
}

void EnemyManager::Clear()
{
    for (auto enemy : enemies) {
        delete enemy;               // ��� �� �޸� ����
    }
    enemies.clear();                // ����Ʈ ����
}

#pragma endregion


