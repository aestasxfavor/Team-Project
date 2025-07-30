#pragma once
#include "Util.h"
#include "ShopUI.h"
#include "Player.h"  // Player 클래스 참조 필요

class Player;
class PlayerStats;

// UIManager: 전체 게임 UI를 통합 관리하는 클래스
// - 체력/경험치 바, 웨이브 타이머, 일시정지, 상점, 스탯 로그 등 포함

class UIManager
{
private:
    // ---------------------- 기본 객체 ----------------------

    Player* player;             // 플레이어 객체 포인터 (has-a 관계)
    PlayerStats* stats;         // 플레이어 스탯

    sf::Font font;              // 공통 폰트

    // ---------------------- 텍스트 요소 ----------------------

    sf::Text timerText;         // 웨이브 타이머 텍스트
    sf::Text titleText;         // 타이틀 화면용 텍스트
    sf::Text startText;         // 시작 안내 텍스트
    sf::Text gameOverText;      // 게임 오버 텍스트

    // ---------------------- 웨이브 관련 ----------------------

    sf::Text waveText;          // 웨이브 넘버 텍스트
    float waveTextTimer = 0.f;  // 웨이브 텍스트 표시 타이머
    bool showWaveText = false;  // 웨이브 텍스트 출력 여부

    sf::Clock waveClock;        // 웨이브 타이머
    bool isWaveActive = false;  // 웨이브 타이머 작동 여부

    // ---------------------- 체력/경험치 UI ----------------------

    sf::RectangleShape hpBarBack;    // 체력바 배경
    sf::RectangleShape hpBarFront;   // 체력바 실제 값

    sf::RectangleShape expBarBack;   // 경험치바 배경
    sf::RectangleShape expBarFront;  // 경험치바 실제 값

    sf::Text hpText;            // 체력 수치 (ex. "9 / 20")
    sf::Text levelText;         // 레벨 수치 (ex. "Lv.5")

    sf::Sprite profileIcon;     // 플레이어 프로필 이미지
    sf::Texture profileTexture; // 프로필 이미지 텍스처

    // 그림자 효과용 텍스트
    sf::Text hpTextShadow;
    sf::Text levelTextShadow;

    // 경험치 애니메이션용 비율
    float currentExpRatio = 0.f;
    float targetExpRatio = 0.f;

    // ---------------------- 스탯 로그 UI ----------------------

    vector<wstring> statLogs;  // 최근 선택 스탯 로그
    sf::RectangleShape statLogBox;       // 로그 감싸는 네모 UI
    sf::Text statLogTexts[3];            // 최근 3개 스탯 로그 출력용

    // ---------------------- 일시정지 UI ----------------------

    bool isPaused = false;          // 일시정지 상태
    bool prevEscPressed = false;    // 이전 ESC 입력 상태
    bool prevMousePressed = false;  // 이전 마우스 입력 상태

    sf::RectangleShape pauseBox;    // 일시정지 네모 박스
    sf::Text resumeText;            // "계속하기"
    sf::Text exitText;              // "나가기"

    float elapsedBeforePause = 0.f; // 일시정지 전 누적 시간
    bool isWavePaused = false;      // 웨이브 일시정지 여부

public:
    // ---------------------- 상점 UI ----------------------

    ShopUI shopUI; // 상점 UI 객체 (has-a 관계)

    // ---------------------- 함수 선언 ----------------------

    // 전체 UI 초기화
    void Init();

    // 프레임 단위 UI 갱신
    void Update(float dt);

    // UI 렌더링
    void Render(sf::RenderWindow& window);

    // 체력/경험치 관련
    void InitStatusUIBar();
    void UpdateHPBar(int currentHp, int maxHp);
    void UpdateExpBar(int currentExp, int maxExp);
    void SetPlayer(Player* _player);
    void UpdateStatusUI();

    // 체력/레벨 그림자 텍스트 초기화
    void statusShadowText();

    // 타이머/웨이브 관련
    void InitTimeText();
    void InitWaveText();
    void UpdateWaveTimerText();
    void ResetWaveTimer();
    float GetWaveElapsedTime() const;
    void ResumeWaveTimer();
    void PauseWaveTimer();
    void ShowWaveText(int wave);

    // 일시정지 관련
    void InitPauseUI();
    void RenderPauseUI(sf::RenderWindow& window);
    bool IsMouseOverResume(const sf::Vector2f& mousePos);
    bool IsMouseOverExit(const sf::Vector2f& mousePos);
    void SetPaused(bool paused);

    // 상점 관련
    void InitShop(PlayerStats& playerStats);
    void OpenShop(PlayerStats& playerStats);
    void UpdateShop(const sf::Vector2f& pos, bool isClick);
    void RenderShop(sf::RenderWindow& window);
    bool IsShopOpen() const;

    // 스탯 로그 관련
    void AddStatLog(const std::wstring& log);
    void InitStatLogUI(sf::Font& font);
    void RenderStatLog(sf::RenderWindow& window);

    // 전체 UI 상태 초기화 (리셋용)
    void Reset();

    void ClearStatLog();
};


