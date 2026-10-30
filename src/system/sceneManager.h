#pragma once
#include <string>
#include <unordered_map>
#include "Scene.h"

class SceneManager {
private:
    std::unordered_map<std::string, Scene*> scenes;
    Scene* currentScene;

    SceneManager();

public:
    static SceneManager& getInstance();

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    ~SceneManager();

    void addScene(const std::string& title, Scene* scene);

    void removeScene(const std::string& title);

    void switchTo(const std::string& title);

    void update(float dt);

    void render();

    Scene* getCurrentScene() const;
};