#pragma once
#include <SFML/Graphics.hpp>
#include <set>

class Enemy;
class PlayerStats;

class Bullet {
private:
    // 이미지
    sf::Sprite bulletSprite;
    sf::Texture bulletTexture;

    // 벡터
    sf::Vector2f direction;
    float bulletSpeed = 300.f;     

    float rotationSpeed = 360.f;

    float lifeTime = 0.f;           // 총알 수명 체크용
    const float maxLifeTime = 2.f;  // 총알 최대 수명
    //에너미 충돌관련
    set<Enemy*> damagedEnemies;
    bool isActive = true;               // 활성화 여부 체크
    bool hasDirectionInit = false;     // 벡터 초기화 상태인지 아닌지

    PlayerStats* stats = nullptr;
public:
  
    Bullet(const sf::Vector2f& startPos, const sf::Vector2f& dir,PlayerStats* stats);
    
    void Update(float deltaTime, const vector<Enemy*>& enemies);
    void Render(sf::RenderWindow& window);

    bool IsActive() const { return isActive; }

    const sf::Vector2f& GetPosition() const { return bulletSprite.getPosition(); }
};