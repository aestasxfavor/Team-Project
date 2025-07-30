#pragma once
#include "Util.h"
#include "Scene.h"

class GameScene; // 전방 선언: GameScene 클래스 필요

class SceneManager; // 전방 선언: SceneManager 클래스 필요

class GameOverScene : public Scene
{
private:
	
	sf::Font font;              // 폰트
	sf::Text gameOverText;      // "게임 오버" 텍스트
	sf::Text restartText;       // "R 키를 눌러 다시 시작" 텍스트
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Clock clock; // 애니메이션 타이머용 시계

	vector<sf::Text> animatedTextLetters;
	float animationTimer = 0.f;
public:	
	void Init() override;        // 초기화 함수
	void Update(sf::RenderWindow& window) override; // 업데이트 함수
	void Render(sf::RenderWindow& window) override; // 렌더링 함수
	virtual ~GameOverScene() = default; // 소멸자
};

