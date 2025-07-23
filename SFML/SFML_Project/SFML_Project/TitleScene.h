#pragma once
#include "Util.h"
#include "Scene.h"
#include "SceneManager.h"

// 2025-07-23 효 추가: 타이틀 씬 클래스 정의
class TitleScene : public Scene
{
private:
    // 배경
    sf::Texture backgroundTexture;
    sf::Sprite background;

    //// 타이틀 로고 (애니메이션용)
    //sf::Texture titleTexture;
    //sf::Sprite title;
    //float titleScaleTimer = 0.f;  // 커졌다 작아졌다 애니메이션 타이머

    //// 버튼: 시작
    //sf::Texture startBtnTexture;
    //sf::Sprite startButton;
    //float startScaleTimer = 0.f;  // 커졌다 작아졌다 애니메이션 타이머

    //// 버튼: 종료
    //sf::Texture exitBtnTexture;
    //sf::Sprite exitButton;
    //float exitScaleTimer = 0.f;  // 커졌다 작아졌다 애니메이션 타이머

    sf::Font font;
	sf::Text titleText;
    sf::Text startText;
    sf::Text exitText;
public:
    void Init();
    void Update(sf::RenderWindow& window);
    void Render(sf::RenderWindow& window);


};

