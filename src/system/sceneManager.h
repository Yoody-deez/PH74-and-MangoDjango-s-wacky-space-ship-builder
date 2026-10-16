#pragma once
#include <string>
#include <unordered_map>
#include "Scene.h"

using namespace std;

class SceneManager {
private:
    unordered_map<string, Scene*> scenes;
    Scene* currentScene;

    SceneManager() : currentScene(nullptr) {}

public:
    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    ~SceneManager() {
        for (auto& pair : scenes) {
            delete pair.second;
        }
        scenes.clear();
    }

    void addScene(const string& title, Scene* scene) {
        if (scene && scenes.find(title) == scenes.end()) {
            scenes[title] = scene;
        }
    }

    void removeScene(const string& title) {
        auto it = scenes.find(title);
        if (it != scenes.end()) {
            if (currentScene == it->second) {
                currentScene->unload();
                currentScene = nullptr;
            }
            delete it->second;
            scenes.erase(it);
        }
    }

    void switchTo(const string& title) {
        auto it = scenes.find(title);
        if (it != scenes.end()) {
            if (currentScene) {
                currentScene->unload();
            }
            currentScene = it->second;
            currentScene->load();
            cout << "Changement de scène vers : " << title << endl;
        } else {
            cerr << "ERREUR::SceneManager::SCENE_INTROUVABLE : " << title << endl;
        }
    }

    void update(float dt) {
        if (currentScene) {
            currentScene->update(dt);
        }
    }

    void render() {
        if (currentScene) {
            currentScene->render();
        }
    }

    Scene* getCurrentScene() const { return currentScene; }
};