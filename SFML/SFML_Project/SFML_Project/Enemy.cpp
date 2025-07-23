#include "Enemy.h"

// 생성자: 텍스처를 스프라이트에 설정하고, 적의 시작 위치를 지정
Enemy::Enemy(sf::Texture& texture, sf::Vector2f spawnPos)
{
    sprite.setTexture(texture);      // 적 이미지 설정
    sprite.setPosition(spawnPos);    // 적 위치 설정

    
}

// 매 프레임 호출, 플레이어 위치를 받아 적을 플레이어 쪽으로 이동시킴
void Enemy::Update(float dt, sf::Vector2f playerPos)
{
    
    sf::Vector2f dir = playerPos - sprite.getPosition();  // 플레이어와 적 위치 차이 벡터 계산
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);  // 두 점 사이 거리 계산

    if (length != 0) {
        dir /= length;                        // 방향 벡터를 단위 벡터로 정규화
        sprite.move(dir * speed * dt);       // 방향 * 속도 * 시간만큼 이동
    }
}



// 적을 화면에 그림
void Enemy::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);   // 윈도우에 스프라이트 렌더링
}

// 데미지를 입으면 체력 감소, 체력이 0 이하가 되면 죽음 상태로 변경
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

    
}

int Enemy::GetAtk() const
{
    return atk;
}

sf::FloatRect Enemy::GetGlobalBounds()
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
