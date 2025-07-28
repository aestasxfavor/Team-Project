#include "Spear.h"
#include "Enemy.h"
#include "Player.h"
#include "Util.h"
#include <cmath>



Spear::Spear(Player* owner) :owner(owner)
{
	
	spearTexture.loadFromFile(GetrscPath("Spear_1.png"));
	
	sprite.setTexture(spearTexture);

	sprite.setOrigin(spearTexture.getSize().x / 2.f, spearTexture.getSize().y / 2.f);
	sf::Vector2f plusVector = { 100.f,100.f };
	sprite.setPosition(owner->GetPosition() + plusVector);
	sprite.setScale(0.05f, 0.05f);
}

void Spear::Update(float deltatime, const std::vector<Enemy*>& enemies)
{
	timer += deltatime;
	if (!fired)
	{
	
		float minDist = 999999.f;
		target = nullptr;
		for (auto e : enemies)
		{
			if (!e || !e->isAlive) continue; // 널 또는 죽은 적이라면 pass
			float dist = std::hypot(e->GetGlobalBounds().getPosition().x - sprite.getPosition().x,
				e->GetGlobalBounds().getPosition().y - sprite.getPosition().y);
			if (dist < minDist)
			{
				minDist = dist;
				target = e;
			}
		}
		
		if (target && target->isAlive) // 타겟이 유효한 상태인지 검사
		{
			sf::Vector2f toTarget = target->GetGlobalBounds().getPosition() - sprite.getPosition();
			float len = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);
			if (len != 0)
			{
				direction = toTarget / len;
			}
			float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;
			sprite.setRotation(angle - 90);
		}
		else
		{
			// 적이 하나도 없으면 랜덤 방향 설정
			float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f;
			direction = sf::Vector2f(std::cos(angle), std::sin(angle));
			float deg = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
			sprite.setRotation(deg - 90);
		}
		if (timer >= delay)
		{
			fired = true;
			timer = 0.f;
		}
	}
	else
	{
		sprite.move(direction * speed * deltatime);
	}

}
void Spear::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool Spear::IsFinished() const
{
	return fired && timer >= 2.f;	// 쏜 상태고 2초? 언저리 지났으면 
}

bool Spear::Checkcollision(Enemy* enemy)
{
	return sprite.getGlobalBounds().intersects(enemy->GetGlobalBounds());
}
sf::Vector2f Spear::GetPosition() const
{
	return sprite.getPosition();
}