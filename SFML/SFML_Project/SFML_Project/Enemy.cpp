
#include "StageManager.h"  // TryFire에서 필요
#include "Enemy.h"
#include "Stage.h"

// ======================= Enemy 기본 클래스 ==========================

// 생성자
Enemy::Enemy(sf::Texture& texture, sf::Vector2f spawnPos)
{
    sprite.setTexture(texture);
    sprite.setPosition(spawnPos);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    sprite.setScale(scale);  // 디폴트값
}



// 기본 이동 로직
void Enemy::Update(float dt, sf::Vector2f playerPos)
{
    sf::Vector2f dir = playerPos - sprite.getPosition();
    //cout << sprite.getPosition().x << " , " << sprite.getPosition().y << endl;
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

    // 2025-07-23 데미지 코드 보류 
  /*  if (amount <= 0)
    {
        cout << "음수 처리 안되게" << amount << endl;
        return;
    }*/

    hp -= amount;          // 데미지 만큼 체력 차감

    //std::cout << "[슬라임 피격] 현재 HP: " << hp << std::endl;
    if (hp <= 0)           // 체력 0 이하이면
        dead = true;       // 죽음 표시

    

    hp -= amount;
    if (hp <= 0)
        dead = true;


    hp -= amount;
    if (hp <= 0)
        dead = true;


    // 2025-07-23 데미지 코드 보류 
  /*  if (amount <= 0)
    {
        cout << "음수 처리 안되게" << amount << endl;
        return;
    }*/

    hp -= amount;          // 데미지 만큼 체력 차감

    //std::cout << "[슬라임 피격] 현재 HP: " << hp << std::endl;
    if (hp <= 0)           // 체력 0 이하이면
        dead = true;       // 죽음 표시


}

// 사망 여부
bool Enemy::IsDead() const
{
    return dead;
}

Enemy::~Enemy()
{
   // std::cout << "  작동!" << std::endl;
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



void slime::Update(float dt, sf::Vector2f playerPos)
{
    Enemy::Update(dt, playerPos);  // 기존 이동 로직

    animationTimer += dt;
    if (animationTimer >= frameDuration)
    {
        animationTimer = 0.f;
        currentFrame = (currentFrame + 1) % frameCount;

        sprite.setTextureRect(sf::IntRect(currentFrame * frameSize.x, 0, frameSize.x, frameSize.y));
    }
    //투사체
    bulletTimer += dt;
    if (bulletTimer >= bulletCooldown)
    {
        bulletTimer = 0.f;

        sf::Vector2f dir = playerPos - sprite.getPosition();
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len != 0)
            dir /= len;

        // EnemyManager가 발사 기능 가지고 있음
        // → 여기서는 직접 호출할 수 없으니 EnemyManager에서 강제로 처리하는 방식 사용
    }
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
void Enemy::TryFire(StageManager* manager, sf::Vector2f playerPos)
{
    // 기본 적은 아무것도 안 함
}

// ======================= enemy01 ==========================

// enemy01 생성자
enemy01::enemy01(sf::Texture& texture, sf::Vector2f spawnPos)
    : Enemy(texture, spawnPos)
{

    hp = 3;

    atk = 5;

    atk = 12;

    hp = 15;
    atk = 5;

    speed = 70.f;

    frameSize = { 64, 64 };
    frameCount = 3;
    frameDuration = 0.2f;

    sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
    sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f);

    sprite.setScale(2.0f, 2.0f); // 확대 동일하게해야 이쁨
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

        int left = currentFrame * frameSize.x;
        sprite.setTextureRect(sf::IntRect(left, 0, frameSize.x, frameSize.y));
    }
}

//        sprite.setTextureRect(sf::IntRect(currentFrame * frameSize.x, 0, frameSize.x, frameSize.y));
//    }
//}

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
void enemy01::TryFire(StageManager* manager, sf::Vector2f playerPos)
{
    manager->FireBulletAtPlayer(GetPosition(), playerPos, atk);
}


// ======================= enemy01 ==========================

// enemy02 생성자
enemy02::enemy02(sf::Texture& texture, sf::Vector2f spawnPos)
    : Enemy(texture, spawnPos)
{

    hp = 3;

    atk = 4;

    atk = 12;

    hp = 15;
    atk = 4;

    speed = 70.f;

    frameSize = { 64, 64 };
    frameCount = 3;
    frameDuration = 0.2f;

    sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
    sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f);
    sprite.setScale(2.0f, 2.0f); // 확대 동일하게해야 이쁨
}

// enemy02::Update
void enemy02::Update(float dt, sf::Vector2f playerPos)
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

// enemy02::CanFire
bool enemy02::CanFire(float dt)
{
    bulletTimer += dt;
    if (bulletTimer >= bulletCooldown)
    {
        bulletTimer = 0.f;
        return true;
    }
    return false;
}

// enemy02::TryFire
void enemy02::TryFire(StageManager* manager, sf::Vector2f playerPos)
{
    manager->FireBulletAtPlayer(GetPosition(), playerPos, atk);
}


// ======================= enemy01 ==========================

// enemy03 생성자
enemy03::enemy03(sf::Texture& texture, sf::Vector2f spawnPos)
    : Enemy(texture, spawnPos)
{

    hp = 3;

    atk = 6;

    atk = 12;

    hp = 15;
    atk = 6;

    speed = 70.f;

    frameSize = { 64, 64 };
    frameCount = 3;
    frameDuration = 0.2f;

    sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
    sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f);
    sprite.setScale(2.0f, 2.0f); // 확대 동일하게해야 이쁨
}

// enemy03::Update
void enemy03::Update(float dt, sf::Vector2f playerPos)
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

// enemy03::CanFire
bool enemy03::CanFire(float dt)
{
    bulletTimer += dt;
    if (bulletTimer >= bulletCooldown)
    {
        bulletTimer = 0.f;
        return true;
    }
    return false;
}

// enemy03::TryFire
void enemy03::TryFire(StageManager* manager, sf::Vector2f playerPos)
{
    manager->FireBulletAtPlayer(GetPosition(), playerPos, atk);
}

