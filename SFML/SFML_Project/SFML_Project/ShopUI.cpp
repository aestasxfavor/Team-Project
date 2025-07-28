#include "ShopUI.h"

void ShopUI::Init(sf::Font& font)
{
    panel.setSize({ 400, 300 });
    panel.setFillColor(sf::Color(50, 50, 50, 200));
    panel.setPosition(200, 150);

    sf::Vector2f panelPos = panel.getPosition();
    sf::Vector2f panelSize = panel.getSize();
    float panelCenterX = panelPos.x + panelSize.x / 2.f;

    for (int i = 0; i < 3; i++)
    {
        // 아이템 텍스트
        itemTexts[i].setFont(font);
        itemTexts[i].setString("Item " + std::to_string(i + 1));
        itemTexts[i].setCharacterSize(24);
        itemTexts[i].setFillColor(sf::Color::White);
        itemTexts[i].setPosition(panelPos.x + 20, panelPos.y + 20 + i * 60);

        // 선택 버튼
        selectButtons[i].setSize({ 80, 30 });
        selectButtons[i].setFillColor(sf::Color(100, 100, 200));
        selectButtons[i].setPosition(panelPos.x + panelSize.x - 100, panelPos.y + 20 + i * 60);
    }

    closeButton.setSize({ 100, 40 });
    closeButton.setFillColor(sf::Color(150, 50, 50));
    closeButton.setPosition(panelCenterX - 50, panelPos.y + panelSize.y - 60);

    closeButtonText.setFont(font);
    closeButtonText.setString("Close");
    closeButtonText.setCharacterSize(24);
    closeButtonText.setFillColor(sf::Color::White);
    closeButtonText.setPosition(panelCenterX - 25, panelPos.y + panelSize.y - 55);
}

void ShopUI::Open(PlayerStats& playerStats)
{
	isOpen = true;
    isButtonClicked = false;

    selectedIndex = -1;

    // 선택지 생성
    selectedStatChoices = playerStats.GetRandomChoices(playerStats.GetStatPool(), 3);

    for (int i = 0; i < 3; i++)
    {
        itemTexts[i].setString(selectedStatChoices[i].name);  // 스탯 이름 표시
        // 등급별 색상 적용
        const std::wstring& grade = selectedStatChoices[i].Grade;

        if (grade == L"A")
            selectButtons[i].setFillColor(sf::Color(255, 230, 0));  // 노랑
        else if (grade == L"B")
            selectButtons[i].setFillColor(sf::Color(0, 200, 100));  // 초록
        else
            selectButtons[i].setFillColor(sf::Color(120, 120, 120)); // 회색
    }
	
}

void ShopUI::Close()
{
	isOpen = false;
    isButtonClicked = false; // 버튼 클릭 상태 초기화
    std::cout << "[ShopUI] Shop Closed" << std::endl;

    if (onCloseCallback)      // ← 콜백 등록되어 있으면
        onCloseCallback();    // ← 실행!

}

bool ShopUI::IsOpen() const
{
	return isOpen;
}

void ShopUI::Update(const sf::Vector2f& mousePos, bool isClick)
{
    if (!isOpen) return;

    // --- 선택 버튼 누름 ---
    for (int i = 0; i < 3; i++)
    {
        if (isClick && selectButtons[i].getGlobalBounds().contains(mousePos))
        {
            selectedIndex = i;
            std::cout << "Item " << i + 1 << " Selected" << std::endl;
            isButtonClicked = true;

            /*if (onSelectCallback)
                onSelectCallback(i);*/
            return;
        }
    }

    // --- Close 버튼 누름 ---
    if (isClick && closeButton.getGlobalBounds().contains(mousePos))
    {
        std::cout << "Close button clicked" << std::endl;

        if (isButtonClicked && onSelectCallback)
        {
            onSelectCallback(selectedIndex); // 선택한 값 전달
            Close();
        }
        else
        {
            std::cout << "[ShopUI] 먼저 스탯을 선택해주세요!" << std::endl;
        }

        return;
    }
}

void ShopUI::Render(sf::RenderWindow& window)
{
    if (!isOpen) return;

   // std::cout << "[ShopUI] 렌더 호출됨" << std::endl;

    window.draw(panel);

    for (int i = 0; i < 3; i++) 
    {
        window.draw(itemTexts[i]);
        window.draw(selectButtons[i]);
    }

    window.draw(closeButton);
    window.draw(closeButtonText);
}

void ShopUI::SetOnSelect(std::function<void(int)> cb)
{
    { onSelectCallback = cb; }
}

void ShopUI::SetOnClose(std::function<void()> callback)
{
    onCloseCallback = callback;
}
