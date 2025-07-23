#pragma once
#include "Util.h"
#include <SFML/Graphics.hpp>

class Enemy {
protected :
    sf::Sprite sprite;      // 적의 이미지와 위치를 나타내는 스프라이트
    int hp = 100;           // 적의 체력 초기값 100
    int atk = 10;           //공격력
    bool dead = false;      // 적이 죽었는지 여부
    float speed = 5.f;    // 적의 이동 속도 (픽셀/초 단위)
    


public:
    Enemy(sf::Texture& texture, sf::Vector2f spawnPos);
    // 생성자: 텍스처와 스폰 위치를 받아 스프라이트 초기화

    virtual void Update(float dt, sf::Vector2f playerPos);
    // 매 프레임 호출, 플레이어 위치를 참고해 적 움직임 및 상태 갱신

    void Draw(sf::RenderWindow& window);
    // 적을 화면에 그리기

    bool IsDead() const { return dead; }
    // 적이 죽었는지 여부 반환 (상수 함수)

    void TakeDamage(int amount);
    // 적이 데미지를 입었을 때 체력을 깎고 죽음 여부 판단
    sf::FloatRect GetGlobalBounds();//충돌관련
    int GetAtk() const;//적이 유저에게 가하는 피해 
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



class enemy01 : public Enemy {
public:
    enemy01(sf::Texture& texture, sf::Vector2f spawnPos)
        : Enemy(texture, spawnPos)
    {
        hp = 2;
        speed = 70.f;
        atk = 15;

        frameSize = { 64, 64 };           // 실제 다람쥐 프레임 크기
        frameCount = 3;                   // 프레임 수

        sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
        sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f);
    }

    void Update(float dt, sf::Vector2f playerPos) override;

private:
    int currentFrame = 0;
    float animationTimer = 0.f;
    float frameDuration = 0.2f;
    int frameCount;
    sf::Vector2i frameSize;

};