#include "UIManager.h"
#include "PlayerStats.h"

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
	//InitStatLogUI(font); // 스탯 로그 UI 초기화

    // player가 Init() 전에 아직 nullptr 아니면 SetPlayer() 함수 안에서 등록하기
    if (player != nullptr)
        InitShop(*player->stats);
	
}

void UIManager::Update(float dt)
{
   // option.
   
 
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
    //RenderStatLog(window);
    // 6. 원래 뷰 복원
    window.setView(originalView);
}

void UIManager::InitTimeText()
{
    // 타이머 텍스트 설정
    timerText.setFont(font);
    timerText.setCharacterSize(45);
    timerText.setFillColor(sf::Color::White);
    
    sf::FloatRect bounds = timerText.getLocalBounds();
    timerText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    timerText.setPosition(1920.f / 2.f, 140.f);  // 조금 아래
    //timerText.setPosition(1920.f / 2.f, 60.f);
}

void UIManager::InitWaveText()
{
    // Wave 텍스트 설정
    waveText.setFont(font);
    waveText.setCharacterSize(45);
    waveText.setFillColor(sf::Color::White);
    waveText.setString("99");
    // 중심 잡기
    sf::FloatRect bounds = waveText.getLocalBounds();
    waveText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    waveText.setPosition(1920.f / 2.f, 100.f);  // 위쪽
    //waveText.setPosition(1920.f / 2.f, 100.f); // 적절한 중앙 위치로 조정
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
    profileIcon.setScale(1.5f, 1.5f);
    profileIcon.setPosition(30.f, 30.f);  // 화면 좌상단 여백 20

    // 2. 체력 바 (아이콘 오른쪽)
    hpBarBack.setSize({ 300.f, 20.f });
    hpBarBack.setFillColor(sf::Color(50, 50, 50));
    hpBarBack.setPosition(130.f, 38.f);  // 아이콘보다 살짝 아래

    hpBarFront.setSize({ 300.f, 20.f });
    hpBarFront.setFillColor(sf::Color::Red);
    hpBarFront.setPosition(130.f, 38.f);

    // 3. 경험치 바 (체력바 아래)
    expBarBack.setSize({ 300.f, 10.f });
    expBarBack.setFillColor(sf::Color(30, 30, 30));
    expBarBack.setPosition(130.f, 62.f);  // 체력바 아래쪽에 여백

    expBarFront.setSize({ 300.f, 10.f }); // 초기값
    expBarFront.setFillColor(sf::Color::Green);
    expBarFront.setPosition(130.f, 62.f);

    // 4. 체력 수치 텍스트 (hpBar 오른쪽 위쪽 정렬)
    hpText.setFont(font);
    hpText.setCharacterSize(18);
    hpText.setFillColor(sf::Color::White);
    hpText.setPosition(130.f + 300.f - 70.f, 38.f);  // 체력바 오른쪽에 위치

    // 5. 레벨 텍스트 (hp 위에 살짝)
    levelText.setFont(font);
    levelText.setCharacterSize(18);
    levelText.setFillColor(sf::Color::White);

    sf::FloatRect expBounds = expBarBack.getGlobalBounds();
    sf::FloatRect lvBounds = levelText.getLocalBounds();

    // 경험치 바 오른쪽 끝 + 약간의 여백
    levelText.setPosition(450.f, 52.f);

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
    timerText.setPosition(1920.f / 2.f, 70.f); // y값 조절
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
    waveText.setPosition(1920.f / 2.f, 30.f); // 위쪽 위치
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
    hpBarFront.setSize({ 300.f * ratio, 20.f });

    // 텍스트 갱신
    std::string hpStr = std::to_string(currentHp) + " / " + std::to_string(maxHp);
    hpText.setString(hpStr);
    hpTextShadow.setString(hpStr); // 그림자 텍스트도 같이

    // 위치 조정 (수치 길이 달라질 수도 있으니까 고정 말고 벡터로)
    sf::Vector2f pos(345.f, 34.f);
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
    expBarFront.setSize({ 300.f * ratio, 10.f }); // 너비는 200 기준
    expBarFront.setPosition(130.f, 62.f); 
    
    // 수치 느낌 애니메이션용 저장
    targetExpRatio = ratio;
}

void UIManager::InitShop(PlayerStats& playerStats)
{
    shopUI.SetOnSelect([&](int index) 
        {
        if (index >= 0)
        {
            const auto& option = shopUI.GetSelectedChoices()[index];
            std::wcout << L"[DEBUG] 선택된 옵션: " << option.name << L" +" << option.amount << std::endl;


            // 선택된 옵션을 플레이어에게 적용
            playerStats.ApplyStat(option);

            AddStatLog(option.name + L" +" + std::to_wstring(option.amount));

        }

        // 상점 닫기 (선택하든 말든)
        shopUI.Close();
        });

    shopUI.SetOnClose([&]() {
        std::cout << "[UIManager] 상점 닫힘 콜백 호출됨" << std::endl;
        // 여기에 다음 웨이브 시작 트리거나 외부 함수 호출 가능
        });
}

void UIManager::OpenShop(PlayerStats& playerStats)
{
   shopUI.Open(playerStats);
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

void UIManager::AddStatLog(const std::wstring& log)
{
    std::wcout << L"[StatLog 추가됨] " << log << std::endl;

    statLogs.push_back(log);
    if (statLogs.size() > 3)
        statLogs.erase(statLogs.begin());

    for (int i = 0; i < statLogs.size(); ++i)
    {
        statLogTexts[i].setString(statLogs[i]);
    }
}

void UIManager::InitStatLogUI(sf::Font& font)
{
    statLogBox.setSize({ 220.f, 100.f });
    statLogBox.setFillColor(sf::Color(30, 30, 30, 200)); // 반투명한 회색
    statLogBox.setOutlineColor(sf::Color::White);
    statLogBox.setOutlineThickness(2.f);
    statLogBox.setPosition(550.f, 20.f); // 오른쪽 상단

    for (int i = 0; i < 3; ++i)
    {
        statLogTexts[i].setFont(font);
        statLogTexts[i].setCharacterSize(16);
        statLogTexts[i].setFillColor(sf::Color::White);
        statLogTexts[i].setPosition(560.f, 30.f + i * 25.f);
    }
}

void UIManager::RenderStatLog(sf::RenderWindow& window)
{
    window.draw(statLogBox);
    for (int i = 0; i < statLogs.size(); i++)
    {
        window.draw(statLogTexts[i]);
    }
}


