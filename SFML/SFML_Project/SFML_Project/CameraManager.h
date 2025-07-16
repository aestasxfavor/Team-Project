#pragma once
#include "Util.h"
#include "Player.h"


/*
  CameraController
  ---------------
  • 플레이어를 화면 중심에 두고 따라다니는 뷰(View)를 관리합니다.
  • 충돌 시 흔들기(shake) 효과를 제공합니다.
  • 투사체 업그레이드 시 일정 시간 줌인/줌아웃 효과를 제공합니다.
*/
class CameraManager
{
public:
    // window: 렌더링 윈도우
    // player: 카메라가 추적할 대상
    CameraManager(sf::RenderWindow* window, Player* player);

    // 매 프레임 호출: 뷰 업데이트, 흔들기 및 줌 효과 적용
    void update(float dt);

    // 최종 렌더링 시 사용할 뷰
    const sf::View& getView() const { return view; }

    // 일정 시간 동안 흔들기 효과를 트리거
    // duration: 흔들리는 총 시간 (초)
    // magnitude: 흔들림 강도 (픽셀 단위)
    void shake(float duration, float magnitude = 5.f);

    // 일정 시간 동안 줌인 효과를 트리거
    // factor: 줌인 비율 (예: 0.8이면 20% 줌인)
    // duration: 효과 지속 시간 (초)
    void triggerZoom(float factor, float duration);

private:
    sf::RenderWindow* window;
    Player* player;
    sf::View          view;

    // 원래 뷰 정보 (복구용)
    sf::Vector2f      defaultCenter;
    sf::Vector2f      defaultSize;

    // 흔들기 상태
    float             shakeTimer = 0.f;
    float             shakeMag = 0.f;

    // 줌 상태
    float             zoomTimer = 0.f;
    float             zoomDuration = 0.f;
    float             zoomFactor = 1.f;
    bool              zooming = false;

    // 랜덤 흔들기용 엔진
    std::default_random_engine      rng;
    std::uniform_real_distribution<float> dist;
};