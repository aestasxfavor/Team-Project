#pragma once
#include "Util.h"
#include "Scene.h"
#include "Stage.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Game.h"

// 전역 델타타임 변수 (시간 간격)
static float deltaTime = 0.f;

// 2025-07-23 효 추가: 게임 씬 클래스 정의
class GameScene : public Scene
{
private:
    // ======= 게임 구성 요소 =======

    UIManager uiManager;           // 전체 UI를 담당하는 매니저
    Stage* stage;                  // 플레이어 및 적이 포함된 스테이지
    Player* player;                // 플레이어 객체 (stage 내부에서 생성)
    StageManager* stageManager;    // 적 스폰 및 웨이브 진행 관리
    PlayerStats playerStats;       // 플레이어 능력치 관리
    SceneManager* sceneManager;    // 씬 전환을 담당하는 매니저
    Game* game;                    // 게임 상태 전체 (레벨, 스탯 선택 등)

    // ======= 시간 관련 =======

    sf::Clock clock;              // 경과 시간 측정용 시계

    // ======= 웨이브/상점 상태 플래그 =======

    bool waveEnded = false;        // 웨이브 종료 여부
    float waveEndTimer = 0.f;      // 웨이브 종료 후 상점 대기 시간

    bool wasShopOpen = false;      // 이전 프레임 상점 열림 여부
    bool prevMousePressed = false; // 마우스 클릭 여부 기록

    bool prevEscPressed = false;   // ESC 키 중복 입력 방지용
    bool wasPausedBefore = false;  // 일시정지 상태 기록

public:
    GameScene();                  // 생성자
    ~GameScene();                 // 소멸자

    void Init() override;                         // 게임 씬 초기화
    void Update(sf::RenderWindow& window) override; // 게임 로직 업데이트
    void Render(sf::RenderWindow& window) override; // 렌더링 처리
    void ResetGame();                             // 게임 상태 리셋
};
