#include "StageManager.h"
#include "UIManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Stage.h"
#include "PlayerStats.h"
#include "SoundManager.h"



// [2025.07.23 수정] 원래 EnemyManager에서 하던 적 생성/관리를 StageManager로 통합함
// 앞으로 적 관련 함수는 StageManager에서 관리함 (ex. FireBulletAtPlayer, UpdateEnemies 등)
// 요거 중요해요!!!!

// 2025-07-24 효 추가 : 메인으로 코멘트 달기위한 주석입니다 :)

StageManager::StageManager()
{
	spawnInterval = 0.3f;    // 적 생성 간격을 5초로 설정
	spawnTimer = 0.f;       // 생성 타이머 초기화
	player = nullptr;
	uiManager = nullptr; // UI 매니저 초기화
	soundManager.LoadAttackSound(GetSoundPath("Defensed_Vert.wav"));
}


StageManager::~StageManager()
{
	Clear();                // 소멸자에서 적들 메모리 정리
}

void StageManager::Init()
{

	player->Init(); // 효 추가 : 플레이어 초기화
	//enemyTexture.loadFromFile("enemy.png");  // 적 텍스처 파일 로드
	//추가


	 // enemy01 이미지
	string path01 = GetrscPath("enemy01.png");
	if (!enemy01Texture.loadFromFile(path01))
	{
		cout << "enemy01.png 로딩 실패! 경로: " << path01 << endl;
	}

	// enemy02 이미지
	string path02 = GetrscPath("enemy02.png");
	if (!enemy02Texture.loadFromFile(path02))
	{
		cout << "enemy02.png 로딩 실패! 경로: " << path02 << endl;
	}

	// enemy03 이미지
	string path03 = GetrscPath("enemy03.png");
	if (!enemy03Texture.loadFromFile(path03))
	{
		cout << "enemy03.png 로딩 실패! 경로: " << path03 << endl;
	}

	// 투사체
	bulletTexture.loadFromFile(GetrscPath("bullet.png"));
}

void StageManager::Update(float dt, sf::Vector2f playerPos)
{
	player->Update(dt, enemies); // 효 추가 : 플레이어 업데이트
	player->GainExperience();
	spawnTimer += dt;       // 누적된 시간 갱신
	shootTimer += dt;
	if (spawnTimer >= spawnInterval && enemies.size() < maxEnemies)   // 생성 간격이 지나면
	{
		SpawnEnemy(playerPos);    // 새로운 적 생성 유저를 기준으로 떨어지게 생성
		spawnTimer = 0.f;        // 타이머 초기화
	}

	if (shootTimer >= 0.9f)
	{
		player->Attack(enemies); // 1초마다 발사
		shootTimer = 0.f ;
		
		soundManager.PlayAttackSound(); // 플레이어 공격 사운드 재생
	}

	// 역순으로 적 리스트 순회 (삭제 안정성 확보)
	for (int i = enemies.size() - 1; i >= 0; --i)
	{
		enemies[i]->Update(dt, playerPos);  // 적 개별 업데이트

		//나를 향해 투사체를 쏜다.
		if (enemies[i]->CanFire(dt)) {
			enemies[i]->TryFire(this, playerPos);
		}

		if (enemies[i]->IsDead())
		{         // 적이 죽었으면
			enemies[i]->isAlive = false;
			Stage::killCount++;
			cout << "KillCount : " << Stage::killCount << endl;
			delete enemies[i];               // 메모리 해제
			enemies.erase(enemies.begin() + i);  // 리스트에서 제거
		}
	}
	//투사체관련
	// 1초에 한 번 발사 (간단 테스트용)
	//static float fireTimer = 0.f;
	//fireTimer += dt;
	//if (fireTimer >= 1.f && !enemies.empty())
	//{
	//    sf::Vector2f pos = enemies[0]->GetGlobalBounds().getPosition();
	//    int damage = enemies[0]->GetAtk();
	//    FireBullet(pos, playerPos, damage);  // 인자 3개로 호출
	//    fireTimer = 0.f;
	//}
	//투사체를 이상한데서 발사하게 되는 관계로 주석처리

	// 투사체 발사 뿅뿅
	for (auto& bullet : bullets)
	{
		sf::Vector2f dir = playerPos - bullet.sprite.getPosition();
		float len = sqrt(dir.x * dir.x + dir.y * dir.y);
		if (len != 0) dir /= len;
		bullet.sprite.move(bullet.velocity * dt);
	}
}


void StageManager::SpawnEnemy(sf::Vector2f playerPos)
{

	float angle = static_cast<float>(rand() % 360) * 3.1415926f / 180.f;
	float distance = minSpawnDistance + static_cast<float>(rand()) / RAND_MAX * 300.f;

	sf::Vector2f spawnPos =
	{
		playerPos.x + cos(angle) * distance,
		playerPos.y + sin(angle) * distance
	};


	if (hypot(spawnPos.x - playerPos.x, spawnPos.y - playerPos.y) < 350.f)
		return;
	Enemy* enemy = nullptr;


	int enemyType = rand() % 3;  // 2025-07-26 효 추가 : 3가지 적을 맵에 랜덤으로 생성

	switch (enemyType)
	{
	case 0:
		enemy = new enemy01(enemy01Texture, spawnPos);
		break;
	case 1:
		enemy = new enemy02(enemy02Texture, spawnPos);
		break;
	case 2:
		enemy = new enemy03(enemy03Texture, spawnPos);
		break;
	default:
		break;
	}

	// 방어코드: enemy가 nullptr일 경우를 대비하여 확인 후 push_back
	// enemyType이 예상치 못한 값이거나 switch 문에서 적절한 객체 생성이 생략되었을 때
	// 잘못된 포인터가 enemies에 들어가는 것을 방지한다.
	if (enemy != nullptr)
		enemies.push_back(enemy);
}

void StageManager::Draw(sf::RenderWindow& window)
{

	for (auto& enemy : enemies)
	{
		enemy->Draw(window);        // 각 적을 화면에 그림
	}
	for (auto& bullet : bullets)
	{
		window.draw(bullet.sprite);
	}
	player->Render(window); // 효 추가 : 플레이어 렌더링
}

void StageManager::Clear()
{
	for (auto enemy : enemies)
	{
		delete enemy;               // 모든 적 메모리 해제
	}
	enemies.clear();                // 리스트 비우기
}

vector<Enemy*>& StageManager::GetEnemies()
{
	return enemies;
}

Player* StageManager::GetPlayer()
{
	return player;
}

void StageManager::SetPlayer(Player* _player)
{
	player = _player;
}


//(2025-07-23) 준호님 : 투사체 패턴관련 + 효 추가 : 적이 플레이어를 향해 쏘는 투사체
void StageManager::FireBulletAtPlayer(sf::Vector2f start, sf::Vector2f playerPos, int damage)
{
	sf::Sprite bullet;
	bullet.setTexture(bulletTexture);

	sf::Vector2f dir = playerPos - start;
	float len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len != 0) dir /= len;

	int frame = rand() % 6;
	bullet.setTextureRect(sf::IntRect(frame * 17, 0, 17, 17));
	bullet.setOrigin(8.5f, 8.5f);
	bullet.setPosition(start);

	BulletData b;
	b.sprite = bullet;
	b.velocity = dir * bulletSpeed;
	b.damage = damage;
	bullets.push_back(b);
}



vector<BulletData>& StageManager::GetBullets()
{
	return bullets;
}

void StageManager::SetUIManager(UIManager* _uiManager)
{
	uiManager = _uiManager; // StageManager에 UI 매니저 설정
}

int StageManager::GetCurrentWave() const
{
	return currentWave;
}

void StageManager::SpawnEnemiesForWave(int waveNumber)
{
	cout << "[StageManager] " << waveNumber << " 웨이브 적 생성!" << endl;

	// 기존 적 제거
	Clear();

	// 웨이브 수에 따라 생성할 적 수 결정 (ex: wave * 3 마리)
	int numEnemies = waveNumber * 3;

	for (int i = 0; i < numEnemies; ++i)
	{
		// 플레이어 위치 기준으로 생성할 수 있도록 좌표는 플레이어 기준으로
		sf::Vector2f playerPos = player ? player->GetPosition() : sf::Vector2f(400.f, 300.f);

		SpawnEnemy(playerPos);  // 기존에 만들어둔 랜덤 타입 적 생성 함수
	}
}

void StageManager::Reset()
{
	Clear();  // 모든 적 제거
	bullets.clear();  // 투사체도 초기화

	currentWave = 1;  // 웨이브 초기화
	spawnTimer = 0.f;
	shootTimer = 0.f;
}

void StageManager::SetResetting(bool value)
{
	isResetting = value;
}

bool StageManager::IsResetting() const
{
	return isResetting;
}

void StageManager::NextWave(Player& player, UIManager& uiManager, int selectedIndex, const vector<PlayerStats::StatOption>& selectedChoices)
{
	currentWave++;
	cout << "[StageManager] Wave " << currentWave << " 시작!" << endl;

	// UI 매니저에 웨이브 텍스트 갱신
	if (!IsResetting() && selectedIndex >= 0 && selectedIndex < selectedChoices.size())
	{
		player.stats->ApplyStat(selectedChoices[selectedIndex]);

		wstringstream ss;
		ss << fixed << setprecision(2);

		switch (selectedChoices[selectedIndex].type)
		{
		case StatType::MAXHP: ss << L"체력 + " << selectedChoices[selectedIndex].amount; break;
		case StatType::DAMAGE: ss << L"공격력 + " << selectedChoices[selectedIndex].amount; break;
		case StatType::DEFENSE: ss << L"방어력 + " << selectedChoices[selectedIndex].amount; break;
		case StatType::ATTACKSPEED: ss << L"공격속도 + " << selectedChoices[selectedIndex].amount; break;
		case StatType::MOVESPEED:  ss << L"이동속도 + " << selectedChoices[selectedIndex].amount; break;
		case StatType::CRITICAL: ss << L"크리티컬 + " << selectedChoices[selectedIndex].amount; break;
		default: ss << L"기타"; break;
		}

		wstring statName = ss.str();
		uiManager.AddStatLog(statName);
	}

	// 체력 회복
	if (player.stats)
	{
		player.stats->currentHp = player.stats->maxHp;
	}

	SpawnEnemiesForWave(currentWave);
	

}




void StageManager::FireBullet(sf::Vector2f start, sf::Vector2f target, int damage)
{
	sf::Sprite bullet;
	bullet.setTexture(bulletTexture);

	int frame = rand() % 6;
	bullet.setTextureRect(sf::IntRect(frame * 17, 0, 17, 17));
	bullet.setOrigin(8.5f, 8.5f);
	bullet.setPosition(start);
	bullet.setScale(2.0f, 2.0f);

	sf::Vector2f dir = target - start;
	float len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len != 0) dir /= len;

	BulletData b;
	b.sprite = bullet;
	b.velocity = dir * bulletSpeed;
	b.damage = damage;

	bullets.push_back(b);
}

//원형투사체
void StageManager::FireBulletSpread(sf::Vector2f start)
{
	const int numBullets = 6; // 6방향
	const float angleStep = 360.f / numBullets;

	for (int i = 0; i < numBullets; ++i)
	{
		float angle = angleStep * i * 3.1415926f / 180.f; // 도 -> 라디안 변환
		sf::Vector2f dir(cos(angle), sin(angle));

		sf::Sprite bullet;
		bullet.setTexture(bulletTexture);

		int frame = rand() % 6;
		bullet.setTextureRect(sf::IntRect(frame * 17, 0, 17, 17));
		bullet.setOrigin(8.5f, 8.5f);
		bullet.setPosition(start);
		bullet.setScale(2.f, 2.f);

		BulletData b;
		b.sprite = bullet;
		b.velocity = dir * bulletSpeed; // bulletSpeed는 StageManager 멤버
		b.damage = 10; // 고정값 또는 enemy03에서 넘겨받도록 수정 가능

		bullets.push_back(b);
	}
}
