#include "SceneManager.h"

map<string, Scene*> SceneManager::scenes;
Scene* SceneManager::currentScene = nullptr;

void SceneManager::AddScene(const std::string& name, Scene* scene)
{
    scenes[name] = scene;
}

void SceneManager::ChangeScene(const std::string& name)
{
    if (scenes.count(name))
    {
        currentScene = scenes[name];
        currentScene->Init();
    }
}

void SceneManager::Update(sf::RenderWindow& window)
{
    if (currentScene)
        currentScene->Update(window);
}

void SceneManager::Render(sf::RenderWindow& window)
{
    if (currentScene)
        currentScene->Render(window);
}

Scene* SceneManager::GetScene(const std::string& name)
{
    auto it = scenes.find(name); // scenes는 map<string, Scene*>이어야 함
    if (it != scenes.end())
        return it->second;
    return nullptr;
}
