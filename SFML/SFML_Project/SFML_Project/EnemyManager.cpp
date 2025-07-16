#include "Util.h"
#include "EnemyManager.h"

//EnemyManager::EnemyManager(Player* p, /*StarManager* s,*/ CameraController* c)
//    : player(p), starMgr(s), camera(c), rng(std::random_device{}())
//{
//    loadTextures();
//    spawnClock.restart();
//}
//
//void EnemyManager::loadTextures()
//{
//    if (!tex1.loadFromFile("resrc/ayEnemy1.png") ||
//        !tex2.loadFromFile("resrc/ayEnemy2.png"))
//        throw std::runtime_error("ayEnemyX.png load fail");
//
//    // 픽셀 충돌용 이미지 복사
//    img1 = tex1.copyToImage();
//    img2 = tex2.copyToImage();
//}
//
//
//void EnemyManager::update(float dt)
//{
//    // 5초마다 웨이브 스폰
//    if (spawnClock.getElapsedTime().asSeconds() >= ENEMY_SPAWN_INTERVAL
//        && enemies.size() < MAX_ENEMIES_TOTAL)
//    {
//        spawnWave();
//        spawnClock.restart();
//    }
//
//    // 모든 적 이동 및 플레이어 충돌 체크
//    for (auto it = enemies.begin(); it != enemies.end(); )
//    {
//        // 목표 방향으로 천천히 이동
//        sf::Vector2f dir = player->getPosition() - it->sprite.getPosition();
//        float len = std::hypot(dir.x, dir.y);
//        if (len != 0.f)
//            dir /= len;
//        it->sprite.move(dir * ENEMY_SPEED * dt);
//
//        // 플레이어 충돌 시 카메라 흔들기
//        if (it->sprite.getGlobalBounds().intersects(player->getBounds()))
//            camera->shake(2.f);
//
//        // hp 0 이하면 제거 + 별 드랍
//        if (it->hp <= 0)
//        {
//            starMgr->spawn(it->sprite.getPosition());
//            it = enemies.erase(it);
//        }
//        else
//        {
//            ++it;
//        }
//    }
//}
//
//void EnemyManager::draw(sf::RenderTarget& target) const
//{
//    for (auto const& e : enemies)
//        target.draw(e.sprite);
//}
//
//void EnemyManager::applyDamage(
//    const std::vector<ProjectileManager::Orb>& orbs)
//{
//    // remove–erase 패턴: orb 의 sprite 바운드와 intersects 되면 적 제거
//    enemies.erase(
//        std::remove_if(
//            enemies.begin(),
//            enemies.end(),
//            [&](Enemy& e) {
//                for (auto const& orb : orbs) {
//                    if (e.sprite.getGlobalBounds()
//                        .intersects(orb.sprite.getGlobalBounds()))
//                    {
//                        // 충돌 시 별 드랍
//                        starMgr->spawn(e.sprite.getPosition());
//                        return true;  // 이 적은 지운다
//                    }
//                }
//                return false;  // 충돌 없으면 살아남음
//            }
//        ),
//        enemies.end()
//    );
//}
//
//
//
//
//void EnemyManager::spawnWave()
//{
//    unsigned spawned = 0;
//    while (spawned < ENEMIES_PER_WAVE && enemies.size() < MAX_ENEMIES_TOTAL)
//    {
//        Enemy e;
//        // 랜덤으로 타입 선택 (확률 반반)
//        if (std::uniform_int_distribution<>(0, 1)(rng) == 0) {
//            e.sprite.setTexture(tex1);
//            e.hp = 2;
//        }
//        else {
//            e.sprite.setTexture(tex2);
//            e.hp = 1;
//        }
//
//        // 스폰 위치 결정 (플레이어 기준 300px 이상)
//        sf::Vector2f pos = randomSpawnPosition();
//        e.sprite.setPosition(pos);
//        // 중앙 정렬
//        sf::FloatRect b = e.sprite.getLocalBounds();
//        e.sprite.setOrigin(b.width / 2, b.height / 2);
//
//        enemies.push_back(e);
//        ++spawned;
//    }
//}
//
//void EnemyManager::handlePlayerCollision(Enemy& e)
//{
//}
//
//sf::Vector2f EnemyManager::randomSpawnPosition()
//{
//    // 맵 크기는 배경 이미지 크기(1267x1275) 기준으로 합니다
//    std::uniform_real_distribution<float> dx(0.f, 1267.f);
//    std::uniform_real_distribution<float> dy(0.f, 1275.f);
//    sf::Vector2f center(1267.f / 2, 1275.f / 2);
//
//    // 플레이어에서 최소 ENEMY_MIN_SPAWN_DIST 떨어진 지점이 나올 때까지 반복
//    while (true)
//    {
//        sf::Vector2f candidate(dx(rng), dy(rng));
//        float dist = std::hypot(candidate.x - center.x, candidate.y - center.y);
//        if (dist >= ENEMY_MIN_SPAWN_DIST)
//            return candidate;
//    }
//}
//
//// EnemyManager.hpp 에서
//std::vector<std::unique_ptr<Enemy>> enemies;
//
//// spawnWave
//void EnemyManager::spawnWave() {
//    unsigned spawned = 0;
//    while (spawned < ENEMIES_PER_WAVE && enemies.size() < MAX_ENEMIES_TOTAL) {
//        std::unique_ptr<Enemy> e;
//        if (std::uniform_int_distribution<>(0, 1)(rng) == 0) {
//            e = std::make_unique<Stage1Enemy>();
//            e->sprite.setTexture(tex1);
//            e->hp = 2;
//        } else {
//            e = std::make_unique<Stage2Enemy>();
//            e->sprite.setTexture(tex2);
//            e->hp = 1;
//        }
//        // 위치 설정
//        sf::Vector2f pos = randomSpawnPosition();
//        e->sprite.setPosition(pos);
//        sf::FloatRect b = e->sprite.getLocalBounds();
//        e->sprite.setOrigin(b.width / 2, b.height / 2);
//
//        enemies.push_back(std::move(e));
//        ++spawned;
//    }
//}


#include "Stage1Enemy.hpp"          // 일단 보류


// 적 상태 업데이트, 이동 등 처리
void EnemyManager::update(float dt)
{
    for (auto& enemy : enemies) 
    {
        enemy->update(dt);

        // 예: 플레이어와 충돌 시 카메라 흔들기
        if (enemy->sprite.getGlobalBounds().intersects(player->getBounds())) 
        {
            camera->shake(2.f);
            // 추가 데미지 처리 등 가능
        }
    }

    // 죽은 적 제거
    enemies.erase(
        remove_if(enemies.begin(), enemies.end(),
            [](const unique_ptr<Enemy>& e) 
            {
                return e->isDead();
            }),
        enemies.end());
}

// 적 그리기
void EnemyManager::draw(sf::RenderTarget& target) const
{
    for (const auto& enemy : enemies) 
    {
        target.draw(enemy->sprite);
    }
}

// 웨이브별 적 생성
void EnemyManager::spawnWave()
{
    static mt19937 rng(random_device{}());
    static uniform_int_distribution<> dist(0, 1);

    unsigned spawnCount = 5;  // 예시 웨이브 크기

    for (unsigned i = 0; i < spawnCount; i++) 
    {
        unique_ptr<Enemy> enemy;

        if (dist(rng) == 0) 
        {
            enemy = make_unique<Stage1Enemy>();
            // 적 텍스처 설정 등 추가
        }
        else 
        {
            // 만약 Stage2Enemy 등이 있다면 여기에 생성
            enemy = make_unique<Stage1Enemy>();  // 임시 동일 타입
        }

        // 적 초기 위치 설정 (예: 맵 랜덤 위치)
        enemy->sprite.setPosition(100.f * i, 100.f); // 임시 위치

        enemies.push_back(move(enemy));
    }
}



