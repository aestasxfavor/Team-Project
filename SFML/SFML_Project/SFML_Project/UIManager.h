#pragma once
#include "Util.h"

// 2025-07-22 효 추가 : 정확하지 않음 


class UIManager
{
private:
	sf::Font font;
	sf::Text timerText;
	sf::Text titleText;
	sf::Text startText;
	sf::Text gameOverText;


	sf::Clock waveClock;  // 웨이브 30초 타이머용
	bool isWaveActive = false;  // 웨이브 타이머 동작 여부
	// 2025-07-22 효 추가 : UI는 미래의 내가 하나? 하겠지... ㅠ 
	// 일단 필요한거
	// 30초 버티면 다음웨이브니까 시간 띄우기
	// 타이틀 -> 게임시작 -> 게임종료 띄우기 
public:
	void Init();
	void Update();
	void Render(sf::RenderWindow& window);

	void StartWaveTimer();   // 30초 타이머 시작
	void ResetWaveTimer();   // 타이머 리셋

};

