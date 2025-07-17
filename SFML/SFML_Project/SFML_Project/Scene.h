#pragma once
#include "Util.h"
// Scene.h
class Scene 
{
public:
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~Scene() {}
};


