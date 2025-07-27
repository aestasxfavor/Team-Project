#include "UIManager.h"

void UIManager::Init()
{
    if (!font.loadFromFile(GetrscPath("Font/BMJUA_ttf.ttf")))
    {
       cerr << "폰트 로드 실패!" << std::endl;
    }

	InitTimeText(); // 타이머 텍스트 초기화
	InitWaveText(); // 웨이브 텍스트 초기화
	InitStatusUIBar(); // 체력바 및 프로필 아이콘 초기화

    statusShadowText();  //  이거 추가해줘야 그림자 텍스트도 초기화됨

	shopUI.Init(font); // 상점 UI 초기화
	
}

void UIManager::Update(float dt)
{
    // 일단 고정 수치로 기본 체력바 보여주기
 
    if (isWaveActive)
    {
		UpdateWaveTimerText(); // 타이머 텍스트 업데이트
    }
    else
    {
        timerText.setString("");
    }

    if (player != nullptr)
    {
		UpdateHPBar(player->stats->currentHp, player->stats->maxHp);    // 체력 바 업데이트
		UpdateExpBar(player->stats->currentExp, player->stats->exp); // 경험치 바 업데이트

        // 레벨 텍스트
        levelText.setString("Lv." + std::to_string(player->stats->level));
        levelTextShadow.setString("Lv." + std::to_string(player->stats->level));
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

    // UI 요소들 (그림자 포함)
    window.draw(profileIcon);       // 프로필 아이콘

    window.draw(hpBarBack);         // 체력바 배경
    window.draw(hpBarFront);        // 체력바 본체
    window.draw(expBarBack);        // 경험치 배경
    window.draw(expBarFront);       // 경험치 본체

    window.draw(hpTextShadow);      // 체력 텍스트 그림자
    window.draw(hpText);            // 체력 텍스트
    window.draw(levelTextShadow);   // 레벨 텍스트 그림자
    window.draw(levelText);         // 레벨 텍스트

    // 4. Wave 그리기 ( 화면 고정 위치)
    window.draw(waveText);  // ← 이거는 이제 고정 출력

	// 5. 상점 UI 그리기
    RenderShop(window);
    // 6. 원래 뷰 복원
    window.setView(originalView);
}

void UIManager::InitTimeText()
{
    // 타이머 텍스트 설정
    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(800.f / 2.f, 60.f);
}

void UIManager::InitWaveText()
{
    // Wave 텍스트 설정
    waveText.setFont(font);
    waveText.setCharacterSize(30);
    waveText.setFillColor(sf::Color::White);
    waveText.setString("");
    waveText.setPosition(800.f / 2.f, 100.f); // 적절한 중앙 위치로 조정
    waveClock.restart();
}

void UIManager::InitStatusUIBar()
{
    // 1. 프로필 아이콘 (왼쪽 상단)
    if (!profileTexture.loadFromFile(GetrscPath("profile.png"))) 
    {
        std::cerr << "프로필 이미지 로드 실패!" << std::endl;
    }
   /* profileTexture.loadFromFile("profile.png");*/
    profileIcon.setTexture(profileTexture);
    profileIcon.setScale(1.0f, 1.0f);
    profileIcon.setPosition(10.f, 10.f);  // 화면 좌상단 여백 20

    // 2. 체력 바 (아이콘 오른쪽)
    hpBarBack.setSize({ 200.f, 20.f });
    hpBarBack.setFillColor(sf::Color(50, 50, 50));
    hpBarBack.setPosition(80.f, 30.f);  // 아이콘보다 살짝 아래

    hpBarFront.setSize({ 200.f, 20.f });
    hpBarFront.setFillColor(sf::Color::Red);
    hpBarFront.setPosition(80.f, 30.f);

    // 3. 경험치 바 (체력바 아래)
    expBarBack.setSize({ 200.f, 10.f });
    expBarBack.setFillColor(sf::Color(30, 30, 30));
    expBarBack.setPosition(80.f, 55.f);  // 체력바 아래쪽에 여백

    expBarFront.setSize({ 200.f, 10.f }); // 초기값
    expBarFront.setFillColor(sf::Color::Green);
    expBarFront.setPosition(80.f, 55.f);

    // 4. 체력 수치 텍스트 (hpBar 오른쪽 위쪽 정렬)
    hpText.setFont(font);
    hpText.setCharacterSize(16);
    hpText.setFillColor(sf::Color::White);
    hpText.setPosition(290.f, 30.f);  // 체력바 오른쪽에 위치

    // 5. 레벨 텍스트 (hp 위에 살짝)
    levelText.setFont(font);
    levelText.setCharacterSize(16);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(290.f, 10.f);  // hp 텍스트보다 위

}

void UIManager::statusShadowText()
{

    // 체력 텍스트 그림자
    hpTextShadow = hpText;
    hpTextShadow.move(1.f, 1.f);
    hpTextShadow.setFillColor(sf::Color(0, 0, 0, 150));

    // 레벨 텍스트 그림자
    levelTextShadow = levelText;
    levelTextShadow.move(1.f, 1.f);
    levelTextShadow.setFillColor(sf::Color(0, 0, 0, 150));
}

void UIManager::UpdateWaveTimerText()
{
    float elapsed = waveClock.getElapsedTime().asSeconds();
    int timeLeft = 30 - static_cast<int>(elapsed);
    if (timeLeft < 0) timeLeft = 0;

    timerText.setString(std::to_string(timeLeft));

    // 중앙 정렬 유지하려면 Origin 다시 설정
    sf::FloatRect textBounds = timerText.getLocalBounds();
    timerText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    timerText.setPosition(400, 70); // y값 조절
}

void UIManager::ResetWaveTimer()
{
    waveClock.restart();
	isWaveActive = true;  // 웨이브 타이머 활성화
}

float UIManager::GetWaveElapsedTime() const
{
    return waveClock.getElapsedTime().asSeconds(); // 실제 시간 반환
}

void UIManager::ShowWaveText(int wave)
{
    // 웨이브 텍스트는 계속 표시됨 (flag 필요 X)
    showWaveText = true;
    waveTextTimer = 2.5f;

    waveText.setString("Wave " + std::to_string(wave));

    // 중앙 정렬 다시 맞춰주기!
    sf::FloatRect bounds = waveText.getLocalBounds();
    waveText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    waveText.setPosition(400, 30); // 위쪽 위치
}

void UIManager::SetPlayer(Player* _player)
{
    player = _player;
}

void UIManager::UpdateHPBar(int currentHp, int maxHp)
{
    float ratio = static_cast<float>(currentHp) / maxHp;
    if (ratio < 0.f) ratio = 0.f;
    if (ratio > 1.f) ratio = 1.f;

    // 체력바 크기 조절
    hpBarFront.setSize({ 200.f * ratio, 20.f });

    // 텍스트 갱신
    std::string hpStr = std::to_string(currentHp) + " / " + std::to_string(maxHp);
    hpText.setString(hpStr);
    hpTextShadow.setString(hpStr); // 그림자 텍스트도 같이

    // 위치 조정 (수치 길이 달라질 수도 있으니까 고정 말고 벡터로)
    sf::Vector2f pos(190.f, 28.f);
    hpText.setPosition(pos);
    hpTextShadow.setPosition(pos + sf::Vector2f(1.f, 1.f));
}

sf::Color UIManager::GetHPColor(float ratio)
{
    return sf::Color();
}

sf::Color UIManager::GetExpColor(float ratio)
{
    return sf::Color();
}

void UIManager::UpdateExpBar(int currentExp, int maxExp)        
{
    // 경험치 비율 계산
    float ratio = static_cast<float>(currentExp) / maxExp;
    if (ratio < 0.f) ratio = 0.f;
    if (ratio > 1.f) ratio = 1.f;

    // 경험치 바 길이 조절
    expBarFront.setOrigin(0.f, 0.f); // 왼쪽 기준
    expBarFront.setSize({ 200.f * ratio, 10.f }); // 너비는 200 기준
    expBarFront.setPosition(80.f, 55.f); 
    
    // 수치 느낌 애니메이션용 저장
    targetExpRatio = ratio;
}

void UIManager::OpenShop()
{
   shopUI.Open();
}

void UIManager::UpdateShop(const sf::Vector2f& pos, bool isClick)
{
    { shopUI.Update(pos, isClick); }
}

void UIManager::RenderShop(sf::RenderWindow& window)
{
     shopUI.Render(window); 
}

bool UIManager::IsShopOpen() const
{
    { return shopUI.IsOpen(); }
}


