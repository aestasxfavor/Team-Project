#pragma once
#include "Util.h"
#include "Scene.h"
#include "SceneManager.h"

class Scene;

// 2025-07-23 효 추가: 타이틀 씬 클래스 정의
class TitleScene : public Scene     // Scene 클래스를 상속받아 타이틀 씬 구현
{
private:
    sf::Font font;              // 폰트
    sf::Text titleText;         // "게임 제목" 텍스트
    sf::Text startText;         // "Enter 키를 눌러 시작하세요" 텍스트

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    float scaleDirection = 1.0f;  // 커지는 방향 (1: 커짐, -1: 작아짐)
    float scaleSpeed = 0.5f;     // 크기 변화 속도
    float minScale = 0.9f;       // 최소 크기 배율
    float maxScale = 1.1f;       // 최대 크기 배율


    bool canStart = true;      // 입력 대기 상태 처리 (애니메이션용 등)
public:
    void Init() override;
    void Update(sf::RenderWindow& window) override;
    void Render(sf::RenderWindow& window) override;


};

