#pragma once
#include "Util.h"
#include "Scene.h"
//#include "TitleScene.h"
#include "WaveManager.h"

// 2025-07-23 효 추가: 씬 매니저 클래스 정의 (스프라이트 시트 구해서 테스트 예정)
class SceneManager 
{
public:
    static void AddScene(const std::string& name, Scene* scene);
    static void ChangeScene(const std::string& name);
    static void Update(sf::RenderWindow& window);
    static void Render(sf::RenderWindow& window);
    static Scene* GetScene(const std::string& name);  // 씬 이름으로 씬 가져오기

private:
    static map<std::string, Scene*> scenes;
    static Scene* currentScene;
};