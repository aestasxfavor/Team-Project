#pragma once
#include "Util.h"
// 2025-07-23 효 추가 : 씬 관리 인터페이스 정의
// 씬 인터페이스를 상속받아 각 씬을 구현할 수 있음.
class Scene  
{
public:
    virtual void Init() {}
    virtual void Update(sf::RenderWindow& window) {}
    virtual void Render(sf::RenderWindow& window) {}
    virtual ~Scene() {}
};
