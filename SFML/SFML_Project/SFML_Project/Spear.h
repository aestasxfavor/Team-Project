#pragma once
#include "Util.h"
#include <SFML/Graphics.hpp>
#include <vector>


class Enemy;
class Player;


// 효 추가 : 아마도 무기 인터페이스용(?) 
// 총, 칼, 부메랑, 레이저 같은거 만들때 상속해서 쓰면 될거같다.
class Spear
{
private:
	Player* owner;
	sf::Sprite sprite;
	sf::Texture spearTexture;

	const vector<Enemy*> enemy;

	float timer = 0.f;				// 타이머 계산용	
	float delay = 1.f;				// 1초 기다렸다 확인 용도
	float speed = 300.f;
	bool fired = false;

	sf::Vector2f direction;
	Enemy* target = nullptr;
public:
	int spearDamage = 10;
	Spear(Player* owner);
	void Update(float deltatime, const vector<Enemy*>& enemies);
	void Render(sf::RenderWindow& window);
	bool IsFinished() const; // 창의 수명이 끝났는 지..
	bool Checkcollision(Enemy* enemy);		//충돌 함수
	sf::Vector2f GetPosition() const;
};


