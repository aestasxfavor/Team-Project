#include "UIManager.h"

void UIManager::Init()
{
    if (!font.loadFromFile(GetrscPath("Font/BMJUA_ttf.ttf")))
    {
        std::cerr << "폰트 로드 실패!" << std::endl;
    }
    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(400, 300);
    waveClock.restart();
}

void UIManager::Update()
{
    if (isWaveActive)
    {
        float elapsed = waveClock.getElapsedTime().asSeconds();
        int timeLeft = 30 - static_cast<int>(elapsed);
        if (timeLeft < 0) timeLeft = 0;

        timerText.setString(std::to_string(timeLeft));

        // 윈도우 크기 예: 800x600
        float windowWidth = 800.f;  // 실제 게임 창 크기로 바꿔줘
        float margin = 10.f;  // 오른쪽 끝에서 10px 떨어지게

        float textWidth = timerText.getLocalBounds().width;
        timerText.setPosition(windowWidth - textWidth - margin, margin);
    }
    else
    {
        timerText.setString("");
    }
}

void UIManager::Render(sf::RenderWindow& window)
{
    // 1. 현재 뷰 저장
    sf::View originalView = window.getView();

    // 2. 기본 뷰(화면 고정 뷰)로 변경
    window.setView(window.getDefaultView());
    // 3. UI 그리기 (화면 고정 위치에 그려짐)
    window.draw(timerText);
    // 4. 원래 뷰 복원
    window.setView(originalView);
}

void UIManager::StartWaveTimer()
{
    waveClock.restart();
	isWaveActive = true;  // 웨이브 타이머 활성화
}

void UIManager::ResetWaveTimer()
{

}
