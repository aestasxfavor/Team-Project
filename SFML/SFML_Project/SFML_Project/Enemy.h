#pragma once
#include "Util.h"

class Enemy
{
public:
	int hp;
	float x, y; // Áö¿öµµ µÊ
	float speed;

	sf::Texture texture;
	sf::Sprite spriteEnemy;
public:
	void Init();
	void Update();
};

