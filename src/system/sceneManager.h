#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include "Scene.h"

class sceneManager {
private:
    std::unordered_map<std::string, scene*> scenes;
    scene* currentScene;

public:
    sceneManager() : currentScene(nullptr) {}

    ~sceneManager() {
        for (auto& pair : scenes) {
            delete pair.second;
        }
        scenes.clear();
    }

    void addScene(const std::string& title, scene* scene) {
        if (scene && scenes.find(title) == scenes.end()) {
            scenes[title] = scene;
        }
    }

    void removeScene(const std::string& title) {
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

    void switchTo(const std::string& title) {
        auto it = scenes.find(title);
        if (it != scenes.end()) {
            if (currentScene) {
                currentScene->unload();
            }
            currentScene = it->second;
            currentScene->load();
            std::cout << "Changement de scène vers : " << title << std::endl;
        } else {
            std::cerr << "ERREUR::SCENEMANAGER::SCENE_INTROUVABLE : " << title << std::endl;
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

    scene* getCurrentScene() const { return currentScene; }
};