#include "SceneManager.h"

// ==========================================================
// [정적 멤버 정의]
// ==========================================================

// 모든 씬을 저장하는 맵 (name → Scene*)
map<string, Scene*> SceneManager::scenes;

// 현재 활성화된 씬
Scene* SceneManager::currentScene = nullptr;

// ==========================================================
// [씬 추가]
// ==========================================================

// 새로운 씬을 scenes 맵에 등록
// - name: 씬 이름 (고유 식별자)
// - scene: 해당 이름에 대응되는 Scene 객체 포인터
// 예: SceneManager::AddScene("Title", new TitleScene());
void SceneManager::AddScene(const string& name, Scene* scene)
{
    scenes[name] = scene;
}

// ==========================================================
// [씬 전환]
// ==========================================================

// 현재 활성 씬을 name에 해당하는 씬으로 변경
// - 해당 씬이 존재하면 currentScene 포인터를 바꾸고 Init() 호출
// - Init() 호출로 씬 내부 초기화 수행
void SceneManager::ChangeScene(const string& name)
{
    if (scenes.count(name))
    {
        currentScene = scenes[name];
        currentScene->Init();  // 씬 전환 시 초기화
    }
    else
    {
        std::cerr << "[SceneManager] 존재하지 않는 씬: " << name << std::endl;
    }
}

// ==========================================================
// [씬 업데이트]
// ==========================================================

// 현재 활성화된 씬의 Update() 호출
// - 매 프레임마다 호출됨 (게임 로직 처리)
void SceneManager::Update(sf::RenderWindow& window)
{
    if (currentScene)
        currentScene->Update(window);
}

// ==========================================================
// [씬 렌더링]
// ==========================================================

// 현재 활성화된 씬의 Render() 호출
// - 매 프레임마다 호출됨 (화면 출력 처리)
void SceneManager::Render(sf::RenderWindow& window)
{
    if (currentScene)
        currentScene->Render(window);
}

// ==========================================================
// [씬 가져오기]
// ==========================================================

// name에 해당하는 씬 포인터를 반환
// - 없으면 nullptr 반환
// - 예: SceneManager::GetScene("Game")
Scene* SceneManager::GetScene(const string& name)
{
    auto it = scenes.find(name);
    if (it != scenes.end())
        return it->second;

    return nullptr;
}
