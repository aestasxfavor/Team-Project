#include "UIManager.h"
#include "PlayerStats.h"

// 게이지 차는거 숫자 띄워서 확인하기 (여기 문제가 큰거같음)

void UIManager::Init()
{
    if (!font.loadFromFile(GetrscPath("Font/BMJUA_ttf.ttf")))
    {
       cerr << "폰트 로드 실패!" << endl;
    }
	InitPauseUI(); // 일시정지 UI 초기화

	InitTimeText(); // 타이머 텍스트 초기화
	InitWaveText(); // 웨이브 텍스트 초기화
	InitStatusUIBar(); // 체력바 및 프로필 아이콘 초기화

    statusShadowText();  //  이거 추가해줘야 그림자 텍스트도 초기화됨

	InitStatLogUI(font); // 스탯 로그 UI 초기화
	shopUI.Init(font); // 상점 UI 초기화


    // player가 Init() 전에 아직 nullptr 아니면 SetPlayer() 함수 안에서 등록하기
    if (player != nullptr)
        InitShop(*player->stats);
	
}

void UIManager::Update(float dt)
{
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
        levelText.setString("Lv." + to_string(player->stats->level));
        levelTextShadow.setString("Lv." + to_string(player->stats->level));
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
    RenderStatLog(window);
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
   
    waveClock.restart();
}

void UIManager::InitStatusUIBar()
{
    // 1. 프로필 아이콘 (왼쪽 상단)
    if (!profileTexture.loadFromFile(GetrscPath("profile.png"))) 
    {
       cerr << "프로필 이미지 로드 실패!" << endl;
    }
   
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
    float elapsed = elapsedBeforePause;

    if (!isWavePaused)  // 일시정지 중이 아니면 현재 경과 시간 추가
        elapsed += waveClock.getElapsedTime().asSeconds();

    int timeLeft = 30 - static_cast<int>(elapsed);
    if (timeLeft < 0) timeLeft = 0;

    timerText.setString(to_string(timeLeft));

    // 중앙 정렬
    sf::FloatRect textBounds = timerText.getLocalBounds();
    timerText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    timerText.setPosition(1920.f / 2.f, 70.f);
}

void UIManager::ResetWaveTimer()
{
    elapsedBeforePause = 0.f;
    waveClock.restart();
	isWavePaused = false;   // 일시정지 상태 해제
	isWaveActive = true;  // 웨이브 타이머 활성화
}

float UIManager::GetWaveElapsedTime() const
{
    if (isWavePaused)
        return elapsedBeforePause;  // 멈춰있는 동안은 이전값 유지

    return elapsedBeforePause + waveClock.getElapsedTime().asSeconds();
}

void UIManager::ResumeWaveTimer()
{
    if (isWavePaused)
    {
        waveClock.restart();// 새 clock 시작  // 일시정지 해제 시, 새로운 시간 측정 시작
        isWavePaused = false;
        cout << "[UIManager] 타이머 재개됨" << endl;
    }
}

void UIManager::PauseWaveTimer()
{
    if (!isWavePaused)
    {
        elapsedBeforePause += waveClock.getElapsedTime().asSeconds();  // 누적시간 저장
        isWavePaused = true;
        cout << "[UIManager] 타이머 일시정지됨, 누적 시간: " << elapsedBeforePause << endl;
    }
}

void UIManager::ShowWaveText(int wave)
{
    // 웨이브 텍스트는 계속 표시됨 (flag 필요 X)
    showWaveText = true;
    waveTextTimer = 2.5f;

    waveText.setString("Wave " + to_string(wave));

    // 중앙 정렬 다시 맞추기
    sf::FloatRect bounds = waveText.getLocalBounds();
    waveText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    waveText.setPosition(1920.f / 2.f, 30.f); // 위쪽 위치
}

void UIManager::SetPlayer(Player* _player)
{
    player = _player;
}

void UIManager::UpdateStatusUI()
{
    cout << "[expBarFront] width: " << expBarFront.getSize().x << endl;     // 여기랑 expbar 보면될거같음 실제값이 0이 들어가야하는데 왜 180이지랄되냐고 그지같네 진짜 

    // 방어 코드
    if (!player || !player->stats)
    {
        std::cerr << "[경고] UIManager::UpdateStatusUI - player 또는 stats가 nullptr입니다!" << std::endl;
        return;
    }

    if (player == nullptr || player->stats == nullptr)
        return;

    PlayerStats* stats = player->stats;

    // 체력바 갱신
    float hpRatio = static_cast<float>(stats->currentHp) / stats->maxHp;
    hpBarFront.setSize({ 300.f * hpRatio, 20.f });
    hpText.setString(to_string(stats->currentHp) + " / " + to_string(stats->maxHp));

    // 경험치바 갱신
    float expRatio = static_cast<float>(stats->currentExp) / stats->exp;        // 왜 초기화가 안될까;;;;;;;;
    expBarFront.setSize({ 300.f * expRatio, 10.f });

    // 레벨 텍스트 갱신
    levelText.setString("Lv." + to_string(stats->level));
}

void UIManager::UpdateHPBar(int currentHp, int maxHp)
{
    float ratio = static_cast<float>(currentHp) / maxHp;
    if (ratio < 0.f) ratio = 0.f;
    if (ratio > 1.f) ratio = 1.f;

    // 체력바 크기 조절
    hpBarFront.setSize({ 300.f * ratio, 20.f });

    // 텍스트 갱신
    string hpStr = to_string(currentHp) + " / " + to_string(maxHp);
    hpText.setString(hpStr);
    hpTextShadow.setString(hpStr); // 그림자 텍스트도 같이

    // 위치 조정 (수치 길이 달라질 수도 있으니까 고정 말고 벡터로)
    sf::Vector2f pos(345.f, 34.f);
    hpText.setPosition(pos);
    hpTextShadow.setPosition(pos + sf::Vector2f(1.f, 1.f));
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
           wcout << L"[DEBUG] 선택된 옵션: " << option.name << L" +" << option.amount << endl;


            // 선택된 옵션을 플레이어에게 적용
            playerStats.ApplyStat(option);

            AddStatLog(option.name + L" +" + to_wstring(option.amount));

        }

        // 상점 닫기 (선택하든 말든)
        shopUI.Close();
        });

    shopUI.SetOnClose([&]() {
        cout << "[UIManager] 상점 닫힘 콜백 호출됨" << endl;
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

void UIManager::AddStatLog(const wstring& log)
{
    wcout << L"[StatLog 추가됨] " << log << endl;

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
    statLogBox.setSize({ 240.f, 120.f });
    statLogBox.setFillColor(sf::Color(30, 30, 30, 200)); // 반투명한 회색
    statLogBox.setOutlineColor(sf::Color::White);
    statLogBox.setOutlineThickness(2.f);
    statLogBox.setPosition(1650.f, 20.f); // 오른쪽 상단

    for (int i = 0; i < 3; ++i)
    {
        statLogTexts[i].setFont(font);
        statLogTexts[i].setCharacterSize(20);
        statLogTexts[i].setFillColor(sf::Color::White);
        statLogTexts[i].setPosition(1700.f, 30.f + i * 24.f);
    }
}


void UIManager::RenderStatLog(sf::RenderWindow& window)
{

    window.draw(statLogBox);
    for (int i = 0; i < statLogs.size(); i++)
    {
    wcout << L"[렌더링 직전 텍스트] " << statLogTexts[i].getString().toWideString() << endl;
        window.draw(statLogTexts[i]);
    }
}

void UIManager::Reset()
{
    // 체력바 및 경험치바 초기화
    hpBarFront.setSize({ 0.f, 20.f });
    expBarFront.setSize({ 0.f, 10.f });

    // 텍스트 초기화
    hpText.setString("");
    hpTextShadow.setString("");
    
    levelText.setString("Lv.1");
    levelTextShadow.setString("Lv.1");

    //expBarBack.setOrigin(0, 0);

    timerText.setString("");
    sf::FloatRect textBounds = timerText.getLocalBounds();
    timerText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    timerText.setPosition(1920.f / 2.f, 70.f);

    // 웨이브 타이머 초기화
    waveClock.restart();
    isWaveActive = true;

    // 스탯 로그 초기화
    statLogs.clear();
    for (int i = 0; i < 3; i++)
    {
        statLogTexts[i].setString(L"");
    }
    // 상점 UI 닫기
    shopUI.Close();
    //InitStatLogUI(font);
}

void UIManager::ClearStatLog()
{
    statLogs.clear();
    cout << "[UIManager] 스탯 로그 초기화됨" << endl;
}

void UIManager::InitPauseUI()
{
    pauseBox.setSize({ 1920.f, 1080.f });
    pauseBox.setPosition(0,0);  // 화면 중앙 기준 위치

    pauseBox.setFillColor(sf::Color(0, 0, 0, 180));

    resumeText.setFont(font);
    resumeText.setCharacterSize(36);
    resumeText.setString("Continue");
    resumeText.setFillColor(sf::Color::White);
    sf::FloatRect resumeBounds = resumeText.getLocalBounds();
    resumeText.setOrigin(resumeBounds.left + resumeBounds.width / 2.f, resumeBounds.top + resumeBounds.height / 2.f);
    resumeText.setPosition(pauseBox.getPosition().x + pauseBox.getSize().x / 2.f,
        pauseBox.getPosition().y + pauseBox.getSize().y / 2.f - 40.f);

    exitText.setFont(font);
    exitText.setCharacterSize(36);
    exitText.setString("Exit");
    exitText.setFillColor(sf::Color::White);
    sf::FloatRect exitBounds = exitText.getLocalBounds();
    exitText.setOrigin(exitBounds.left + exitBounds.width / 2.f, exitBounds.top + exitBounds.height / 2.f);
    exitText.setPosition(pauseBox.getPosition().x + pauseBox.getSize().x / 2.f,
        pauseBox.getPosition().y + pauseBox.getSize().y / 2.f + 40.f);
}

void UIManager::RenderPauseUI(sf::RenderWindow& window)
{
    //  현재 뷰 저장
    sf::View originalView = window.getView();

    //  기본 뷰로 전환 (화면 고정용)
    window.setView(window.getDefaultView());
    window.draw(pauseBox);
    window.draw(resumeText);
    window.draw(exitText);

	window.setView(originalView);   // 원래 뷰로 복원
}

bool UIManager::IsMouseOverResume(const sf::Vector2f& mousePos)
{
    return resumeText.getGlobalBounds().contains(mousePos);
}

bool UIManager::IsMouseOverExit(const sf::Vector2f& mousePos)
{
    return exitText.getGlobalBounds().contains(mousePos);
}

void UIManager::SetPaused(bool paused)
{
    isPaused = paused;
}


