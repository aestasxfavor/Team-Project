#pragma once
#include "Util.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

// ==========================================================
// GameApp 클래스
// - 게임의 메인 실행 클래스 (게임 루프 포함)
// - 윈도우 생성, 씬 초기화, 루프 실행 등을 담당
// ==========================================================

class GameApp
{
private:
    // -------------------- [기본 시스템] --------------------
    sf::RenderWindow window;    // 메인 게임 창
    sf::Clock clock;            // 프레임 시간 측정용 시계

public:
    // -------------------- [생성자] --------------------
    GameApp();                  // 윈도우 초기화 및 설정
    ~GameApp();
    // -------------------- [메인 흐름] --------------------

    // 초기 설정 및 씬 등록
    void Init();

    // 메인 게임 루프 실행 (업데이트 & 렌더 반복)
    void Run();
};
