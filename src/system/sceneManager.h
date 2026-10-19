#pragma once
#include <string>
#include <unordered_map>
#include "Scene.h"

using namespace std;

class SceneManager {
private:
    unordered_map<string, Scene*> scenes;
    Scene* currentScene;

    SceneManager();

public:
    static SceneManager& getInstance();

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    ~SceneManager();

    void addScene(const string& title, Scene* scene);

    void removeScene(const string& title);

    void switchTo(const string& title);

    void update(float dt);

    void render();

    Scene* getCurrentScene() const;
};