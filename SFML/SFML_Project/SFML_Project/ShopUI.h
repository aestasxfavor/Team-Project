#pragma once
#include "Util.h"


// 2025-07-26 효 추가: 상점 UI 클래스 정의
class ShopUI
{
    bool isOpen = false;
    bool isButtonClicked = false;

    sf::RectangleShape panel;
    sf::Text itemTexts[3];
    sf::RectangleShape selectButtons[3];
    sf::RectangleShape closeButton;
    sf::Text closeButtonText;

public:
    void Init(sf::Font& font);
    void Open();
    void Close();
    bool IsOpen() const;

    void Update(const sf::Vector2f& mousePos, bool isClick);
    void Render(sf::RenderWindow& window);

    std::function<void(int)> onSelectCallback;
    std::function<void()> onCloseCallback;  // ← 이거 ShopUI 클래스 멤버로 추가해


    void SetOnSelect(std::function<void(int)> cb);
    void SetOnClose(std::function<void()> callback);
    
};


