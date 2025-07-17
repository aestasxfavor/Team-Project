#pragma once
#include "Util.h"
#include "Scene.h"
// 효 추가 : 게임의 전체적인 흐름 돌리기(필요없을수도 있음 보류)
class Game 
{
private:
    Scene* currentScene;
    //void changeScene(SceneType type); // 타이틀 → 게임 → 결과 씬 전환
public:
    Game() = default;
    ~Game();
    void run(); // 메인 루프


};

