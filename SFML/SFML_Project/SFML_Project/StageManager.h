#pragma once
#include "Util.h"
#include "Enemy.h"
#include "Player.h"

// 2025-07-21 효 추가 (EnemyManager->StageManager 이름 변경)
class StageManager
{
public:
    StageManager();                 // 생성자: 초기 변수 세팅 및 리소스 준비
    ~StageManager();                // 소멸자: 동적 할당된 적들 메모리 해제

    void Init();                   // 초기화: 텍스처 로드 및 초기 변수 설정
    void Update(float dt, sf::Vector2f playerPos);
    // 매 프레임 호출, 적 스폰 시간 계산 및 적 업데이트 처리
    void SpawnEnemy(sf::Vector2f spawnPos);
    // 특정 위치에 새로운 적 생성 및 리스트에 추가

    void Draw(sf::RenderWindow& window);
    // 모든 적을 화면에 그리기
    void Clear();                  // 적 리스트 초기화 및 동적 할당된 적 메모리 해제
    std::vector<Enemy*>& GetEnemies();//충돌관련
    Player* GetPlayer();

	// 효 추가 : Player 객체를 StageManager에 설정
    void SetPlayer(Player* _player);    // 초기화 해주기

private:
   
    Player* player;                 // 효 추가, StageManager가 Player를 내부에 포함함(has - a 관계)
    std::vector<Enemy*> enemies;   // 현재 게임에 존재하는 적들 포인터 리스트
    sf::Texture enemyTexture;      // 적 텍스처 (이미지 데이터)
    float spawnInterval;           // 적 생성 간격 (초)
    float spawnTimer;              // 누적된 시간 (적 생성 시간 체크용)
    float minSpawnDistance = 150.f;
    int maxEnemies = 100;//몬스터 최대치
    //추가
    //enemy 스프라이트 관련 코드
    sf::Sprite spriteSlime;
    sf::Texture texture;
    //적 개체스프라이트
    sf::Texture slimeTexture;
    sf::Texture enemy01Texture;

};
