#include "Player.h"

void Player::Init()
{
	texture.loadFromFile(GetrscPath("Catcharacter.png"));
	spritePlayer.setTexture(texture);
	spritePlayer.setPosition(370.f,280.f);
	spritePlayer.setTextureRect(sf::IntRect(0,40, 48, 48));
	speed = 200.f;
}

void Player::Update(float deltaTime)
{
	sf::Vector2f direction(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction.x -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction.x += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction.y -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction.y += 1;

	if (direction.x != 0 || direction.y != 0)
	{

		state = MOVE;
		Move(deltaTime, direction);
	}
	else
	{
		state = IDLE;
	}
	if (state == MOVE)
	{
		animationTimer += deltaTime;
		if (animationTimer >= frameDuration)
		{
			animationTimer = 0.f;

			// 프레임 전환 (0 ↔ 1)
			currentFrame = (currentFrame + 1) % 2;
		}

		// currentFrame에 따라 워크 이미지 설정
		if (currentFrame == 0)
			spritePlayer.setTextureRect(sf::IntRect(50, 40, 50, 50));  // 첫 번째 WALK 프레임
		else
			spritePlayer.setTextureRect(sf::IntRect(100, 40, 50, 50)); // 두 번째 WALK 프레임
	}
	else
	{
		// IDLE 상태
		spritePlayer.setTextureRect(sf::IntRect(0, 40, 48, 48));
		animationTimer = 0.f;
		currentFrame = 0;
	}
}

void Player::Render(sf::RenderWindow& window)
{
	window.draw(spritePlayer);
}

void Player::Move(float deltaTime, const sf::Vector2f& dir)
{
	sf::Vector2f norm = dir;

	// 방향 벡터 정규화
	float len = std::sqrt(norm.x * norm.x + norm.y * norm.y);

	if (len != 0)
	{
		norm /= len;  // 정규화
		spritePlayer.move(norm * speed * deltaTime);
	}
}

void Player::PickUp()
{
}

void Player::LevelUp()
{
}

void Player::Attack()
{
}

void Player::UseSkill(int slot)
{
}

sf::Vector2f Player::GetPosition() const
{
	return spritePlayer.getPosition();
}
//추가
void Player::Render(sf::RenderWindow& window, const sf::Vector2f& position)
{
	spritePlayer.setPosition(position);
	window.draw(spritePlayer);
}

