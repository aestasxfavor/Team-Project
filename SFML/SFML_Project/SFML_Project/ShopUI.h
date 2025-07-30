#pragma once
#include "Util.h"
#include "PlayerStats.h"  // StatOption 정의가 들어있는 헤더


class PlayerStats;



// 2025-07-26 효 추가: 상점 UI 클래스 정의
class ShopUI
{
    int selectedIndex = -1;  // 기본값은 선택 안 한 상태

    bool isOpen = false;
    bool isButtonClicked = false;

    sf::RectangleShape panel;
    sf::Text itemTexts[3];
    sf::RectangleShape selectButtons[3];
    sf::RectangleShape closeButton;
    sf::Text closeButtonText;
    


    vector<PlayerStats::StatOption> selectedStatChoices;

public:
    void Init(sf::Font& font);
    void Open(PlayerStats& playerStats);
    void Close();
    bool IsOpen() const;

    void Update(const sf::Vector2f& mousePos, bool isClick);
    void Render(sf::RenderWindow& window);

    function<void(int)> onSelectCallback;
   function<void()> onCloseCallback;  //


    void SetOnSelect(function<void(int)> cb);
    void SetOnClose(function<void()> callback);

    const vector<PlayerStats::StatOption>& GetSelectedChoices() const { return selectedStatChoices; }

    void ClearSelectedChoices();
    
};


