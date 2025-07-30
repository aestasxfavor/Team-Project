#pragma once
#include "Util.h"
#include "Scene.h"

// ==========================================================
// SceneManager 클래스
// - 전체 게임의 씬(Scene)을 전역적으로 관리하는 정적 클래스
// - 씬 추가, 전환, 업데이트, 렌더링 등 씬 흐름을 제어함
// - 모든 함수 및 변수는 static (전역에서 접근 가능)
// ==========================================================

class SceneManager
{
public:
    // 새로운 씬 등록
    // - name: 씬 이름
    // - scene: Scene 객체 포인터
    static void AddScene(const string& name, Scene* scene);

    // 현재 씬을 변경
    // - name: 이동할 씬 이름
    static void ChangeScene(const string& name);

    // 현재 씬 업데이트 (게임 루프에서 호출)
    static void Update(sf::RenderWindow& window);

    // 현재 씬 렌더링 (게임 루프에서 호출)
    static void Render(sf::RenderWindow& window);

    // 특정 이름의 씬 포인터를 가져옴
    static Scene* GetScene(const string& name);

private:
    // 등록된 모든 씬을 저장하는 맵 (이름 → 씬 포인터)
    static map<string, Scene*> scenes;

    // 현재 활성화된 씬
    static Scene* currentScene;
};
