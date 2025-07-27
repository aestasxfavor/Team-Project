#include "Player.h"
#include "PlayerStats.h"
#include "Spear.h"
#include "Enemy.h"
#include "Bullet.h"


void Player::Init()
{

	texture.loadFromFile(GetrscPath("Catcharacter2.png"));
	
	spritePlayer.setTexture(texture);
	spritePlayer.setPosition(370.f,280.f);
	spritePlayer.setTextureRect(sf::IntRect(0,40, 48, 48));
	speed = 200.f;

	stats = new PlayerStats;
	
	/*std::string path = GetrscPath("Catcharacter2.png");
	std::cout << "Texture Path: " << path << std::endl;
	if (!texture.loadFromFile(path)) {
		std::cerr << "텍스처 로드 실패: " << path << std::endl;
	}*/
}

void Player::Update(float deltaTime,const std::vector<Enemy*>& enemies)
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
	spearCoolTime += deltaTime;
	if (!spear && spearCoolTime >= 1.f) // 쿨타임이 지났을 때 
	{
		spearCoolTime = 0.f;
		spear = new Spear(this);
	}
	if (spear)
	{
		spear->Update(deltaTime, enemies);

		// 검사 코드
		for (auto e : enemies)
		{
			if (spear->Checkcollision(e))
			{
				e->TakeDamage(spear->spearDamage);
				
				delete spear;
				spear = nullptr;
				break;
			}
		}
		if (spear && spear->IsFinished())
		{
			delete spear;
			spear = nullptr;
		}
	}
	// 미니가 추가한 함수.
	for (auto* bullet : bullets) 
	{
		bullet->Update(deltaTime, enemies); 
	}

	bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
		[](Bullet* b) 
		{
			if (!b->IsActive())
			{
				delete b;
				return true;
			}
			return false;
		}), bullets.end());

	// 피격시 무적
	if (isInvincible)
	{
		invincibleTimer += deltaTime;
		blinkTimer += deltaTime;

		if (blinkTimer >= blinkInterval)
		{
			blinkTimer = 0.f;
			visible = !visible; // 보이기/숨기기 토글
		}

		if (invincibleTimer >= invincibleDuration)
		{
			isInvincible = false;
			invincibleTimer = 0.f;
			visible = true; // 정상 상태 복귀
		}
	}
	else
	{
		visible = true; // 무적 아님 = 항상 보임
	}
}


//무적시간 깜빡임을 위해 약간 손봤습니다.
//원본은 주석처리!
void Player::Render(sf::RenderWindow& window)
{

	if (spear != nullptr)
	{
		spear->Render(window);
	}
	if (visible)
		window.draw(spritePlayer);
	for (auto* bullet : bullets) {
		bullet->Render(window);
	}

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
	stats->LevelUp();
}

void Player::Attack(const std::vector<Enemy*>& enemies)
{
	Enemy* closest = nullptr;
	float minDist = std::numeric_limits<float>::max();
	// 가장 가까운 적 탐색
	for (auto* enemy : enemies) {
		float dist = std::hypot(enemy->GetPosition().x - GetPosition().x,
								enemy->GetPosition().y - GetPosition().y);
		if (dist < minDist) {
			minDist = dist;
			closest = enemy;
		}
	}

	// 방향 벡터 구해서 Bullet 생성
	if (closest)
	{
		sf::Vector2f toTarget = closest->GetPosition() - GetPosition();
		bullets.push_back(new Bullet(GetPosition(), toTarget ,stats));
	}
}



void Player::GainExperience()
{
	stats->GainExp();
}

void Player::AddItemStat(const PlayerStats::StatOption itemStats)
{	
	// 미래에 있을 김동민이 구현할 아이템 얻을 때 스탯 변화
	stats->ApplyStat(itemStats);
}

sf::Vector2f Player::GetPosition() const
{
	return spritePlayer.getPosition();
}
//추가(2025-07-21 준호님 추가)
void Player::Render(sf::RenderWindow& window, const sf::Vector2f& position)
{
	spritePlayer.setPosition(position);
	//window.draw(spritePlayer);
	if (visible)
		window.draw(spritePlayer);
}

//추가(2025-07-21 준호님 추가)
sf::FloatRect Player::GetGlobalBounds() const//충돌관련
{
	return spritePlayer.getGlobalBounds();
}
void Player::TakeDamage(int amount)
{
	if (isInvincible)
		return;

	stats->currentHp -= amount;
	std::cout << "플레이어가 받은 피해: " << amount << std::endl;

	isInvincible = true;
	invincibleTimer = 0.f;
	blinkTimer = 0.f;

	if (stats->currentHp <= 0)
	{
		std::cout << "플레이어가 죽었습니다!" << std::endl;
	}
}

