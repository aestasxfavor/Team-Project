#include "Enemy.h"
#include "EnemyManager.h"  // TryFire에서 필요

// ======================= Enemy 기본 클래스 ==========================

// 생성자
Enemy::Enemy(sf::Texture& texture, sf::Vector2f spawnPos)
{
    sprite.setTexture(texture);
    sprite.setPosition(spawnPos);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}

// 기본 이동 로직
void Enemy::Update(float dt, sf::Vector2f playerPos)
{
    sf::Vector2f dir = playerPos - sprite.getPosition();
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0) dir /= len;

    sprite.move(dir * speed * dt);
}

// 그리기
void Enemy::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

// 피격 처리
void Enemy::TakeDamage(int amount)
{
    hp -= amount;
    if (hp <= 0)
        dead = true;
}

// 사망 여부
bool Enemy::IsDead() const
{
    return dead;
}

// 공격력 반환
int Enemy::GetAtk() const
{
    return atk;
}

// 충돌 영역
sf::FloatRect Enemy::GetGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

// 위치 반환
sf::Vector2f Enemy::GetPosition() const
{
    return sprite.getPosition();
}

// 기본적으로 발사 안 함
bool Enemy::CanFire(float dt)
{
    return false;
}

// 기본적으로 발사 안 함
void Enemy::TryFire(EnemyManager* manager, sf::Vector2f playerPos)
{
    // 기본 적은 아무것도 안 함
}

// ======================= enemy01 ==========================

// enemy01 생성자
enemy01::enemy01(sf::Texture& texture, sf::Vector2f spawnPos)
    : Enemy(texture, spawnPos)
{
    hp = 3;
    atk = 12;
    speed = 70.f;

    frameSize = { 64, 64 };
    frameCount = 3;
    frameDuration = 0.2f;

    sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
    sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f);
}

// enemy01::Update
void enemy01::Update(float dt, sf::Vector2f playerPos)
{
    Enemy::Update(dt, playerPos);

    animationTimer += dt;
    if (animationTimer >= frameDuration)
    {
        animationTimer = 0.f;
        currentFrame = (currentFrame + 1) % frameCount;
        sprite.setTextureRect(sf::IntRect(currentFrame * frameSize.x, 0, frameSize.x, frameSize.y));
    }
}

// enemy01::CanFire
bool enemy01::CanFire(float dt)
{
    bulletTimer += dt;
    if (bulletTimer >= bulletCooldown)
    {
        bulletTimer = 0.f;
        return true;
    }
    return false;
}

// enemy01::TryFire
void enemy01::TryFire(EnemyManager* manager, sf::Vector2f playerPos)
{
    manager->FireBulletAtPlayer(GetPosition(), playerPos, atk);
}
