#pragma once
#include "Util.h"
// 2025-07-23 효 추가 : 씬 관리 인터페이스 정의
// 씬 인터페이스를 상속받아 각 씬을 구현할 수 있음.
// 2025-07-25 효 추가: 씬 인터페이스를 상속받아 구현할 수 있는 기본 씬 클래스 정의0
class Scene  
{
public:
    virtual void Init() = 0;
    virtual void Update(sf::RenderWindow& window) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
	virtual ~Scene() = default;     // 2025-07-25 효 추가: 가상 소멸자 정의
};