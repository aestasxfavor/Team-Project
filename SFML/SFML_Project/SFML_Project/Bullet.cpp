#include "Util.h"
#include "Bullet.h"
#include "Enemy.h"
#include "PlayerStats.h"


Bullet::Bullet(const sf::Vector2f& startPos, const sf::Vector2f& dir, PlayerStats* _stats)
{
    bulletTexture.loadFromFile(GetrscPath("tears_bone.png"));
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setTextureRect(sf::IntRect(223, 4, 20, 40));
    bulletSprite.setOrigin(20 / 2, 40 / 2);
    bulletSprite.setPosition(startPos);
    stats = _stats;
    //  방향 정규화 후 저장
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    direction = (len != 0.f) ? dir / len : sf::Vector2f(1.f, 0.f);

}

void Bullet::Update(float deltaTime , const std::vector<Enemy*>& enemies)
{
    if (!isActive) return;
    
    // 현재 적이 없거나 하면 디폴트 상태로 작동되도록 하는 코드
    if (!hasDirectionInit)
    {
        if (enemies.empty())
        {
            float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f;
            direction = sf::Vector2f(std::cos(angle), std::sin(angle));
        }
        hasDirectionInit = true;
    }
    
    
    // 이동 및 수명 증가
    // Move함수 안에 위에 초기화 하면서 구한거 다 대입하면 날라감
    bulletSprite.move(direction * bulletSpeed * deltaTime);
    
    // 총알 초당 회전속도 대입해서 회전시키기
    bulletSprite.rotate(rotationSpeed * deltaTime);

    
    // 총알 수명 확인용 코드
    lifeTime += deltaTime;
    

    // 총알이 생성된 시간이 2초가 넘을시 false;
    if (lifeTime >= maxLifeTime) 
    {
        isActive = false;
        return;
    }

    // 충돌 체크 (여러 Enemy 가능)
    for (Enemy* enemy : enemies) 
    {
        if (!enemy) continue;
        if (damagedEnemies.count(enemy)) continue; // 이미 맞은 적은 스킵

        if (bulletSprite.getGlobalBounds().intersects(enemy->GetGlobalBounds())) {

            enemy->TakeDamage(stats->damage); // 필요 시 데미지 수치 조정
            damagedEnemies.insert(enemy);

            damagedEnemies.insert(enemy);
            enemy->TakeDamage(stats->damage); // 필요 시 데미지 수치 조정
            cout << "적에게 데미지 " << stats->damage << " 입힘!" << std::endl;

        }
    }
}
void Bullet::Render(sf::RenderWindow& window)
{
    if (isActive)
        window.draw(bulletSprite);
}