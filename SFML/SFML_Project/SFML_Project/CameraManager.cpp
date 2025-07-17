#include "CameraManager.h"

CameraManager::CameraManager(sf::RenderWindow* wnd, Player* ply)
    : window(wnd)
    , player(ply)
    , view(wnd->getDefaultView())
    , rng(std::random_device{}())
    , dist(-1.f, 1.f)
{
    // 기본 뷰 크기와 중심 저장
    defaultSize = view.getSize();
    defaultCenter = view.getCenter();
}

void CameraManager::shake(float duration, float magnitude)
{
    shakeTimer = duration;
    shakeMag = magnitude;
}

void CameraManager::triggerZoom(float factor, float duration)
{
    // 이미 줌 중이면 덮어쓰기
    //zoomFactor = factor;
    //zoomDuration = duration;
    //zoomTimer = duration;
    //zooming = true;

    //// 즉시 줌인 크기로 변경
    //view.setSize(defaultSize * factor);
   
        zoomStartFactor = currentZoomFactor; // 현재 줌 상태에서 시작
        zoomTargetFactor = factor;
        zoomDuration = duration;
        zoomTimer = 0.f;
        zooming = true;

}

void CameraManager::update(float dt)
{
    // 1) 기본적으로 플레이어 위치를 뷰 중심에 맞춘다
    sf::Vector2f center = player->getPosition();

    // 2) 흔들기 효과가 남아 있으면 랜덤 오프셋을 더한다
    if (shakeTimer > 0.f) 
    {
        shakeTimer -= dt;
        float xOff = dist(rng) * shakeMag;
        float yOff = dist(rng) * shakeMag;
        center += { xOff, yOff };
    }

    if (zooming)
    {
        zoomTimer += dt;
        float t = zoomTimer / zoomDuration;

        if (t >= 1.f)
        {
            zooming = false;
            currentZoomFactor = zoomTargetFactor;
            view.setSize(defaultSize * currentZoomFactor);

            // 여기서 스탯 UI 띄우기 트리거 걸어도 됨
            // 예: uiManager->showStatUI();
        }
        else
        {
            // 선형 보간으로 부드럽게 확대
            currentZoomFactor = zoomStartFactor + (zoomTargetFactor - zoomStartFactor) * t;
            view.setSize(defaultSize * currentZoomFactor);
        }
    }


    // 3) 줌 타이머가 끝나면 원래 크기로 복원
    if (zooming) 
    {
        zoomTimer -= dt;
        if (zoomTimer <= 0.f) 
        {
            zooming = false;
            view.setSize(defaultSize);
        }
    }

    // 4) 뷰에 최종 중심 및 크기 적용
    view.setCenter(center);
    window->setView(view);
}