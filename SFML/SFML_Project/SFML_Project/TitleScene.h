#pragma once
#include "Util.h"
#include "Scene.h"
#include "SceneManager.h"

class Scene;

//  TitleScene 클래스
// - 타이틀 화면을 담당하는 씬
// - 게임 제목, 시작 안내 텍스트, 배경 이미지 및 간단한 애니메이션 효과 포함
class TitleScene : public Scene
{
private:
    // -------------------- [텍스트/폰트 관련] --------------------
    sf::Font font;              // 전체 UI에 사용할 공통 폰트
    sf::Text titleText;         // 게임 제목 텍스트
    sf::Text startText;         // "Enter 키를 눌러 시작하세요" 텍스트

    // -------------------- [배경 관련] --------------------
    sf::Texture backgroundTexture;  // 배경 이미지 텍스처
    sf::Sprite backgroundSprite;    // 배경 이미지 스프라이트

    // -------------------- [시간/애니메이션 관련] --------------------
    sf::Clock clock;            // 프레임 시간 계산용 시계

    float scaleDirection;       // 텍스트 크기 변화 방향 (1: 커짐, -1: 작아짐)
    float scaleSpeed;           // 텍스트 크기 변화 속도
    float minScale;             // 텍스트 최소 크기 배율
    float maxScale;             // 텍스트 최대 크기 배율
    float textAnimTimer;        // 텍스트 애니메이션 타이머 누적용

    // -------------------- [배경 스크롤용 스프라이트 2개] --------------------
    sf::Sprite backgroundSprite1;
    sf::Sprite backgroundSprite2;
    float backgroundX1;         // 첫 번째 배경 X 좌표
    float backgroundX2;         // 두 번째 배경 X 좌표
    float backgroundScrollSpeed; // 배경 이동 속도

    // -------------------- [게임 시작 처리 관련] --------------------
    bool canStart;              // 게임 시작 가능 여부 (입력 타이밍 제어)
    bool enterPreviouslyPressed; // 이전 프레임에서 Enter가 눌렸는지 확인

public:
    TitleScene();               // 생성자 - 멤버 변수 초기화 담당
public:
    void Init() override;                       // 타이틀 씬 초기화
    void Update(sf::RenderWindow& window) override;  // 매 프레임 업데이트
    void Render(sf::RenderWindow& window) override;  // 화면 렌더링
};
