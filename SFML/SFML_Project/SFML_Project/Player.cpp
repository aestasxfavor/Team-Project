#include "Player.h"
#include "SceneManager.h"

void Player::Init()
{

	texture.loadFromFile(GetrscPath("Catcharacter2.png"));
	
	spritePlayer.setTexture(texture);
	spritePlayer.setPosition(370.f,280.f);
	spritePlayer.setTextureRect(sf::IntRect(0,40, 48, 48));
	speed = 200.f;
	/*std::string path = GetrscPath("Catcharacter2.png");
	std::cout << "Texture Path: " << path << std::endl;
	if (!texture.loadFromFile(path)) {
		std::cerr << "텍스처 로드 실패: " << path << std::endl;
	}*/
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

	// 미니가 추가한 함수.
	if (!canAttack)
	{
		currentAttackCoolTime += deltaTime;
		if (currentAttackCoolTime >= stats.GetFinalAttackCooldown())
		{
			canAttack = true;
			currentAttackCoolTime = 0.0f;
		}
	}

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
	//window.draw(spritePlayer);
	if (visible)
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
	// 미니가 추가한 함수.
	if (canAttack)
	{
		// 공격 구현 하면 됨.
	}
	else
	{
		// 공격 불가능 상태구현.
	}

}

void Player::UseSkill(int slot)
{
}

void Player::Death()
{
	isDead = true;
	
	SceneManager::ChangeScene("GameOver"); //  여기서 호출
	// 게임 오버 처리 등 추가 로직 필요
}

void Player::GainExperience(int amount)
{
	stats.GainExp(amount);
}

void Player::AddItemStat(const PlayerStats::StatOption itemStats)
{	
	// 미래에 있을 김동민이 구현할 아이템 얻을 때 스탯 변화
	stats.ApplyStat(itemStats);
}

sf::Vector2f Player::GetPosition() const
{
	return spritePlayer.getPosition();
}
//추가(2025-07-21 준호님 추가)
void Player::Render(sf::RenderWindow& window, const sf::Vector2f& position)
{
	spritePlayer.setPosition(position);

	if (visible)
		window.draw(spritePlayer);
}

//추가(2025-07-21 준호님 추가)
sf::FloatRect Player::GetGlobalBounds() const//충돌관련
{
	return spritePlayer.getGlobalBounds();
}
void Player::TakeDamage(int amount)		// 2025-07-26 효 추가 : 플레이어가 데미지 입고 죽는거까지 구현완료
{
	//if (isInvincible||isDead)
	//	return;

	//stats.currentHp -= amount;
	//std::cout << " 현재 체력 : " << stats.currentHp << std::endl;

	//isInvincible = true;
	//invincibleTimer = 0.f;
	//blinkTimer = 0.f;

	//if (stats.currentHp <= 0)
	//{
	//	//std::cout << "플레이어가 죽었습니다!" << std::endl;
	//	Death();
	//}

	if (isInvincible || isDead)
		return;

	stats.currentHp -= amount;
	cout << "[TakeDamage] 현재 체력 : " << stats.currentHp << endl;

	isInvincible = true;
	invincibleTimer = 0.f;
	blinkTimer = 0.f;

	if (stats.currentHp <= 0)
	{
		cout << "[Death 호출 조건 충족]" << endl;
		Death();
	}
}

