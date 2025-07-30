#pragma once
#include "Util.h"

// ==========================================================
// Scene 인터페이스 (순수 가상 클래스)
// - 모든 게임 씬은 이 클래스를 상속받아 구현해야 함
// - 씬 간 공통 인터페이스 역할 수행
// - 예: TitleScene, GameScene, ResultScene 등
// ==========================================================

class Scene
{
public:
    // 씬 초기화 함수
    // - 리소스 로딩, 상태 초기화 등을 수행
    virtual void Init() = 0;

    // 씬 업데이트 함수
    // - 매 프레임마다 호출됨
    // - 이벤트 처리, 게임 로직 수행
    virtual void Update(sf::RenderWindow& window) = 0;

    // 씬 렌더링 함수
    // - 매 프레임마다 호출됨
    // - 화면 출력용 draw() 등 수행
    virtual void Render(sf::RenderWindow& window) = 0;

    // 가상 소멸자 (동적 소멸 안전 보장)
    virtual ~Scene() = default;
};
