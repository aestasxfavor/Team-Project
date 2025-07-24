#pragma once

#include "Util.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

// 전방 선언: TryFire에서 사용
class EnemyManager;

// ======================= 기본 Enemy 클래스 ==========================
class Enemy {
protected:
    sf::Sprite sprite;
    int hp = 100;
    int atk = 10;
    float speed = 50.f;
    bool dead = false;

public:
    Enemy(sf::Texture& texture, sf::Vector2f spawnPos);

    virtual ~Enemy() = default;

    virtual void Update(float dt, sf::Vector2f playerPos);
    virtual void Draw(sf::RenderWindow& window);
    virtual void TakeDamage(int amount);
    virtual bool IsDead() const;
    virtual int GetAtk() const;
    virtual sf::FloatRect GetGlobalBounds() const;
    virtual sf::Vector2f GetPosition() const;

    virtual bool CanFire(float dt);
    virtual void TryFire(EnemyManager* manager, sf::Vector2f playerPos);
};

// ======================= enemy01 클래스 ==========================
class enemy01 : public Enemy {
public:
    enemy01(sf::Texture& texture, sf::Vector2f spawnPos); // 정의는 cpp에서

    void Update(float dt, sf::Vector2f playerPos) override;
    bool CanFire(float dt) override;
    void TryFire(EnemyManager* manager, sf::Vector2f playerPos) override;

private:
    int currentFrame = 0;
    float animationTimer = 0.f;
    float frameDuration = 0.2f;
    int frameCount = 3;
    sf::Vector2i frameSize = { 64, 64 };

    float bulletTimer = 0.f;
    float bulletCooldown = 2.0f;//발사쿨타임
};

// ======================= enemy02 클래스 ==========================


