#include "ShopUI.h"

void ShopUI::Init(sf::Font& font)
{
    panel.setSize({ 400, 300 });
    panel.setFillColor(sf::Color(50, 50, 50, 200));
    panel.setPosition(200, 150);

    for (int i = 0; i < 3; i++) 
    {
        itemTexts[i].setFont(font);
        itemTexts[i].setString("Item " + std::to_string(i + 1));
        itemTexts[i].setCharacterSize(24);
        itemTexts[i].setFillColor(sf::Color::White);
        itemTexts[i].setPosition(220, 170 + i * 60);

        selectButtons[i].setSize({ 80, 30 });
        selectButtons[i].setFillColor(sf::Color(100, 100, 200));
        selectButtons[i].setPosition(450, 170 + i * 60);
    }

    closeButton.setSize({ 100, 40 });
    closeButton.setFillColor(sf::Color(150, 50, 50));
    closeButton.setPosition(300, 390);

    closeButtonText.setFont(font);
    closeButtonText.setString("Close");
    closeButtonText.setCharacterSize(24);
    closeButtonText.setFillColor(sf::Color::White);
    closeButtonText.setPosition(325, 395);
}

void ShopUI::Open()
{
	isOpen = true;
	
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

    if (isClick && closeButton.getGlobalBounds().contains(mousePos))
    {
        std::cout << "Close button clicked" << std::endl;

        isButtonClicked = true;
        if (onSelectCallback)
            onSelectCallback(-1);  // -1은 선택 안함 의미

        Close();
        return;
    }

    for (int i = 0; i < 3; i++)
    {
        if (isClick && selectButtons[i].getGlobalBounds().contains(mousePos))
        {
            isButtonClicked = true;
            std::cout << "Item " << i + 1 << " Selected" << std::endl;

            if (onSelectCallback)
                onSelectCallback(i);  // 버튼 눌렀을 때만 콜백

            return;  // 한 번만 호출하고 끝냄
        }
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
