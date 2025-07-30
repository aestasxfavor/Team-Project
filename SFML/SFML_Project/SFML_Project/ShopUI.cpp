#include "ShopUI.h"

// 상점 UI 초기화
void ShopUI::Init(sf::Font& font)
{
    // [1] 상점 패널 설정
    panel.setSize({ 500.f, 350.f });  // 패널 크기 지정
    sf::Vector2f panelSize = panel.getSize();

    // 정중앙 위치 계산 (1920x1080 해상도 기준)
    sf::Vector2f panelPos = {
        (1920.f - panelSize.x) / 2.f,
        (1080.f - panelSize.y) / 2.f
    };
    panel.setFillColor(sf::Color(50, 50, 50, 200));  // 반투명 회색 배경
    panel.setPosition(panelPos);

    float panelCenterX = panelPos.x + panelSize.x / 2.f;

    // [2] 선택 가능한 스탯 텍스트 및 버튼 초기화
    for (int i = 0; i < 3; i++)
    {
        // 스탯 이름 텍스트
        itemTexts[i].setFont(font);
        itemTexts[i].setCharacterSize(24);
        itemTexts[i].setFillColor(sf::Color::White);
        itemTexts[i].setString("Item " + to_string(i + 1));

        float textY = panelPos.y + 40.f + i * 80.f;
        itemTexts[i].setPosition(panelPos.x + 30.f, textY);

        // 선택 버튼
        selectButtons[i].setSize({ 80.f, 30.f });
        selectButtons[i].setFillColor(sf::Color(100, 100, 200));
        selectButtons[i].setPosition(panelPos.x + panelSize.x - 110.f, textY);
    }

    // [3] 닫기 버튼
    closeButton.setSize({ 100.f, 40.f });
    closeButton.setFillColor(sf::Color(150, 50, 50));
    closeButton.setPosition(panelCenterX - 50.f, panelPos.y + panelSize.y - 60.f);

    // [4] 닫기 버튼 텍스트
    closeButtonText.setFont(font);
    closeButtonText.setString("Close");
    closeButtonText.setCharacterSize(24);
    closeButtonText.setFillColor(sf::Color::White);
    closeButtonText.setPosition(panelCenterX - 30.f, panelPos.y + panelSize.y - 55.f);
}

// 상점 열기 (스탯 선택지 세팅)
void ShopUI::Open(PlayerStats& playerStats)
{
    isOpen = true;
    isButtonClicked = false;
    selectedIndex = -1;

    // 스탯 선택지 3개 랜덤 생성
    selectedStatChoices = playerStats.GetRandomChoices(playerStats.GetStatPool(), 3);

    for (int i = 0; i < 3; i++)
    {
        itemTexts[i].setString(selectedStatChoices[i].name);  // 스탯 이름 표시

        // 등급에 따라 버튼 색상 다르게 설정
        const wstring& grade = selectedStatChoices[i].Grade;

        if (grade == L"A")
            selectButtons[i].setFillColor(sf::Color(255, 230, 0));  // 노랑
        else if (grade == L"B")
            selectButtons[i].setFillColor(sf::Color(0, 200, 100));  // 초록
        else
            selectButtons[i].setFillColor(sf::Color(120, 120, 120)); // 회색
    }
}

// 상점 닫기 (콜백 함수 호출 포함)
void ShopUI::Close()
{
    isOpen = false;
    isButtonClicked = false;  // 클릭 여부 초기화
    cout << "[ShopUI] Shop Closed" << endl;

    // onClose 콜백 함수 등록되어 있으면 호출
    if (onCloseCallback)
        onCloseCallback();
}

// 상점 열려있는지 여부 확인
bool ShopUI::IsOpen() const
{
    return isOpen;
}

// 마우스 클릭 입력 등으로 상점 UI 업데이트
void ShopUI::Update(const sf::Vector2f& mousePos, bool isClick)
{
    if (!isOpen) return;

    // [1] 스탯 선택 버튼 클릭 처리
    for (int i = 0; i < 3; i++)
    {
        if (isClick && selectButtons[i].getGlobalBounds().contains(mousePos))
        {
            selectedIndex = i;
            cout << "Item " << i + 1 << " Selected" << endl;
            isButtonClicked = true;
            return;
        }
    }

    // [2] Close 버튼 클릭 처리
    if (isClick && closeButton.getGlobalBounds().contains(mousePos))
    {
        cout << "Close button clicked" << endl;

        // 선택 먼저 한 경우에만 콜백 실행
        if (isButtonClicked && onSelectCallback)
        {
            onSelectCallback(selectedIndex);  // 선택한 인덱스 전달
            Close();  // 상점 닫기
        }
        else
        {
            cout << "[ShopUI] 먼저 스탯을 선택해주세요!" << endl;
        }
    }
}

// 상점 UI 렌더링
void ShopUI::Render(sf::RenderWindow& window)
{
    if (!isOpen) return;

    window.draw(panel);

    for (int i = 0; i < 3; i++)
    {
        window.draw(itemTexts[i]);
        window.draw(selectButtons[i]);
    }

    window.draw(closeButton);
    window.draw(closeButtonText);
}

// 콜백 함수 등록 함수 (선택 콜백)
void ShopUI::SetOnSelect(function<void(int)> callback)
{
    onSelectCallback = callback;
}

// 콜백 함수 등록 함수 (닫기 콜백)
void ShopUI::SetOnClose(function<void()> callback)
{
    onCloseCallback = callback;
}

const vector<PlayerStats::StatOption>& ShopUI::GetSelectedChoices() const
{
    return selectedStatChoices;
}

// 선택한 스탯 초기화
void ShopUI::ClearSelectedChoices()
{
    selectedStatChoices.clear();
    selectedIndex = -1;
    cout << "[ShopUI] 선택된 스탯 초기화됨" << endl;
}
