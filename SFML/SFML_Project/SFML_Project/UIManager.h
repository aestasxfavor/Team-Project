#pragma once
#include "Util.h"
#include "ShopUI.h"
#include "Player.h" // Player 클래스 필요

// 2025-07-22 효 추가 : 정확하지 않음 

class Player;
class PlayerStats;

class UIManager
{
private:

	Player* player; // 플레이어 객체 포인터 (has - a 관계)
	PlayerStats* stats;
	//vector<StatOption>* option;

	sf::Font font;
	sf::Text timerText;
	sf::Text titleText;
	sf::Text startText;
	sf::Text gameOverText;

	// 웨이브 관련 변수들
	sf::Text waveText;        // 웨이브 표시용 텍스트
	float waveTextTimer = 0.f; // 웨이브 텍스트 표시 시간
	bool showWaveText = false; // 웨이브 텍스트 출력 여부

	// 타이머 관련 변수들
	sf::Clock waveClock;  // 웨이브 30초 타이머용
	bool isWaveActive = false;  // 웨이브 타이머 동작 여부

	// 플레이어 체력관련 변수들
	sf::RectangleShape hpBarBack;     // 체력 바 배경 (검은색 or 회색)
	sf::RectangleShape hpBarFront;    // 체력 바 실제 체력 (빨간색)

	sf::RectangleShape expBarBack;    // 경험치 바 배경
	sf::RectangleShape expBarFront;   // 경험치 바 현재값

	sf::Text hpText;                  // "9 / 20" 같은 체력 수치
	sf::Text levelText;              // "Lv.7" 이런 거

	sf::Sprite profileIcon;          // 원형 캐릭터 프로필 이미지
	sf::Texture profileTexture;

	// 그림자 효과를 위한 텍스트
	sf::Text hpTextShadow;
	sf::Text levelTextShadow;

	// 스탯 로그 관련
	vector<wstring> statLogs;        // 최근 선택 스탯들
	sf::RectangleShape statLogBox;            // 로그 감싸는 네모박스
	sf::Text statLogTexts[3];                 // 로그 출력 텍스트들 (최대 3개)

	float currentExpRatio = 0.f;  // 실제 exp보다 약간 느리게 따라가는 느낌
	float targetExpRatio = 0.f;   // 실제 exp 값 (0~1)


	// 2025-07-22 효 추가 : UI는 미래의 내가 하나? 하겠지... ㅠ 
	// 일단 필요한거
	// 30초 버티면 다음웨이브니까 시간 띄우기 -> 이걸 해야하나
	// 아 소리도 넣어야하구나 -> 확인... 사운드를 어디서... 
	// 타이틀 -> 게임시작 -> 게임종료 띄우기 
public:
	ShopUI shopUI; // 상점 UI 객체 (has - a 관계)
public:
	void Init();
	void Update(float dt);
	void Render(sf::RenderWindow& window);

	void InitTimeText(); // 타이머 텍스트 초기화 (void 함수)
	void InitWaveText(); // 웨이브 텍스트 초기화 (void 함수)
	void InitStatusUIBar(); // 체력바 초기화 (void 함수)
	void statusShadowText(); // 체력바 그림자 텍스트 초기화 (void 함수)
	void UpdateWaveTimerText(); // 웨이브 텍스트 업데이트 (void 함수)

	void ResetWaveTimer();               // 타이머 리셋 (void 함수)
	float GetWaveElapsedTime() const;   // 경과 시간 반환 (float 함수)

	void ShowWaveText(int wave);  // 웨이브 넘길 때 호출

	void SetPlayer(Player* _player);  // 플레이어 설정 (void 함수)
	void UpdateHPBar(int currentHp, int maxHp); // 체력바 업데이트 (void 함수)

	sf::Color GetHPColor(float ratio); // ratio = currentHp / maxHp
	sf::Color GetExpColor(float ratio); // ratio = currentHp / maxHp
	void UpdateExpBar(int currentExp, int maxExp); // 경험치 바 업데이트 (void 함수)

	void InitShop(PlayerStats& playerStats);
	void OpenShop(PlayerStats& playerStats);
	void UpdateShop(const sf::Vector2f& pos, bool isClick);
	void RenderShop(sf::RenderWindow& window);		// 상점 UI 렌더링 (void 함수)

	bool IsShopOpen() const;

	// 스탯 로그 추가 함수
	void AddStatLog(const wstring& log);

	// Init에서 호출할 스탯 로그 초기화 함수
	void InitStatLogUI(sf::Font& font);

	// Render 안에 넣을 함수 (혹은 직접 Render에서 출력해도 됨)
	void RenderStatLog(sf::RenderWindow& window);

};

