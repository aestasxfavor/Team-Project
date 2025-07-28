#pragma once

#include "Util.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

// 전방 선언: TryFire에서 사용
class StageManager;

// ======================= 기본 Enemy 클래스 ==========================
class Enemy {
protected:
    sf::Sprite sprite;
    int hp = 100;
    int atk = 10;
    float speed = 50.f;
    bool dead = false;
    bool isActive = false;

    sf::Vector2f scale = { 1.0f, 1.0f };//이미지크기

public:
    Enemy(sf::Texture& texture, sf::Vector2f spawnPos);
    //동민 추가


    bool isAlive = true;
    virtual ~Enemy();


    virtual void Update(float dt, sf::Vector2f playerPos);
    virtual void Draw(sf::RenderWindow& window);
    virtual void TakeDamage(int amount);
    virtual bool IsDead() const;
    virtual int GetAtk() const;
    virtual sf::FloatRect GetGlobalBounds() const;
    virtual sf::Vector2f GetPosition() const;

    virtual bool CanFire(float dt);

    virtual void TryFire(StageManager* manager, sf::Vector2f playerPos);

    //virtual void TryFire(EnemyManager* manager, sf::Vector2f playerPos);

    void SetScale(sf::Vector2f s); //이미지 크기 조절

};



//적 개체 데이터
//테스트용 슬라임
class slime : public Enemy {
public:
    slime(sf::Texture& texture, sf::Vector2f spawnPos)
        : Enemy(texture, spawnPos)
    {
        hp = 1;
        speed = 60.f;
        atk = 90;
        sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));

        sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f);
    }

    void Update(float dt, sf::Vector2f playerPos) override;
    //투사체관련
    float bulletTimer = 0.f;
    float bulletCooldown = 2.0f;

private:
    int currentFrame = 0;
    float animationTimer = 0.f;
    float frameDuration = 0.2f;
    int frameCount = 7;

    sf::Vector2i frameSize = { 250, 250 };

};






//적 개체 데이터

// ======================= enemy01 클래스 ==========================

class enemy01 : public Enemy {
public:
    enemy01(sf::Texture& texture, sf::Vector2f spawnPos); // 정의는 cpp에서


    //    frameSize = { 64, 64 };           // 실제 다람쥐 프레임 크기
    //    frameCount = 3;                   // 프레임 수

    //    sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
    //    sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f);
    //}

    void Update(float dt, sf::Vector2f playerPos) override;
    /*void Update(float dt, sf::Vector2f playerPos) override;*/
    bool CanFire(float dt) override;
    void TryFire(StageManager* manager, sf::Vector2f playerPos) override;

private:
    int currentFrame = 0;
    float animationTimer = 0.f;
    float frameDuration = 0.2f;
    int frameCount = 3;
    sf::Vector2i frameSize = { 64, 64 };

    float bulletTimer = 0.f;
    float bulletCooldown = 4.0f;//발사쿨타임
};

// ======================= enemy02 클래스 ==========================
class enemy02 : public Enemy {
public:
    enemy02(sf::Texture& texture, sf::Vector2f spawnPos); // 정의는 cpp에서

    void Update(float dt, sf::Vector2f playerPos) override;
    bool CanFire(float dt) override;
    void TryFire(StageManager* manager, sf::Vector2f playerPos) override;

private:
    int currentFrame = 0;
    float animationTimer = 0.f;
    float frameDuration = 0.2f;
    int frameCount = 3;
    sf::Vector2i frameSize = { 64, 64 };

    float bulletTimer = 0.f;
    float bulletCooldown = 6.0f;//발사쿨타임
};

// ======================= enemy03 클래스 ==========================

class enemy03 : public Enemy {
public:
    enemy03(sf::Texture& texture, sf::Vector2f spawnPos); // 정의는 cpp에서

    void Update(float dt, sf::Vector2f playerPos) override;
    bool CanFire(float dt) override;
    void TryFire(StageManager* manager, sf::Vector2f playerPos) override;

private:
    int currentFrame = 0;
    float animationTimer = 0.f;
    float frameDuration = 0.2f;
    int frameCount = 3;
    sf::Vector2i frameSize = { 64, 64 };

    float bulletTimer = 0.f;
    float bulletCooldown = 8.0f;//발사쿨타임
};
