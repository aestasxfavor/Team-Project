#pragma once
#include "Util.h"

class Enemy
{
public:
    sf::Sprite sprite;
    int hp;

    sf::Texture texture;
    sf::Sprite spritePlayer;
    enum State { IDLE, MOVE, ATTACK } state = IDLE;

    Enemy() : hp(1) {}
    virtual ~Enemy() {}

    virtual void update(float dt) 
    {
        // 기본 이동 없음, 하위에서 구현
    }

    virtual bool isDead() const { return hp <= 0; }
};

