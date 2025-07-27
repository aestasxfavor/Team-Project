#include "StageManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Stage.h"

// [2025.07.23 수정] 원래 EnemyManager에서 하던 적 생성/관리를 StageManager로 통합함
// 앞으로 적 관련 함수는 StageManager에서 관리함 (ex. FireBulletAtPlayer, UpdateEnemies 등)
// 요거 중요해요!!!!

// 2025-07-24 효 추가 : 메인으로 코멘트 달기위한 주석입니다 :)

StageManager::StageManager()
{
    spawnInterval = 0.3f;    // 적 생성 간격을 5초로 설정
    spawnTimer = 0.f;       // 생성 타이머 초기화
    player = nullptr;
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

    //테스트용 슬라임 이미지
   //slimeTexture.loadFromFile(GetrscPath("slime.png"));
   //spriteSlime.setTexture(texture);    // 효 추가 : [확인 필요] texture 변수는 slimeTexture와 역할이 겹치는 것 같음 의도가 불분명.. 상의 후 결정하기
   //spriteSlime.setPosition(370.f, 280.f);
    //spriteSlime.setTextureRect(sf::IntRect(0, 227, 227 , 227));'

    
    //enemy01이미지
    std::string path = GetrscPath("enemy01.png");
    if (!enemy01Texture.loadFromFile(path))
    {
        std::cout << "enemy01.png 로딩 실패!" << std::endl;
        std::cout << "시도된 경로: " << path << std::endl;
    }



    //투사체 관련 init
    bulletTexture.loadFromFile(GetrscPath("bullet.png"));
}

void StageManager::Update(float dt, sf::Vector2f playerPos) 
{
	player->Update(dt,enemies); // 효 추가 : 플레이어 업데이트
    
    spawnTimer += dt;       // 누적된 시간 갱신
    shootTimer += dt;
    if (spawnTimer >= spawnInterval && enemies.size()< maxEnemies)   // 생성 간격이 지나면
    {
        SpawnEnemy(playerPos);    // 새로운 적 생성 유저를 기준으로 떨어지게 생성
        spawnTimer = 0.f;        // 타이머 초기화
    }
    if (shootTimer >= 0.9f) 
    {
        player->Attack(enemies); // 1초마다 발사
        shootTimer = 0.f;
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
			player->GainExperience(); // 플레이어 경험치 획득
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
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
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

    Enemy* enemy = nullptr;


    int enemyType = rand() % 2;  // 현재는 2종 (0: slime, 1: enemy01)   // 2025-07-22 14:14분 효 추가 : enum으로 설계해도 될거 같음 일단 보류하기 

    //int enemyType = rand() % 1;  // 현재는 1종으로 적 class 수 만큼 늘려주세요.      2025-07-24 01:10분 효 추가 : 밑에 또는 위에거 둘중 하나 사용할거같음


    switch (enemyType)
    {
    case 0:
        enemy = new enemy01(enemy01Texture, spawnPos);
        break;
    //case 1:
    //    break;
    //case 2:
    //    enemy = new enemy02(enemy01Texture, spawnPos);
    //    break;
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
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
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



std::vector<BulletData>& StageManager::GetBullets()
{
    return bullets;
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
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0) dir /= len;

    BulletData b;
    b.sprite = bullet;
    b.velocity = dir * bulletSpeed;
    b.damage = damage;  

    bullets.push_back(b);
}