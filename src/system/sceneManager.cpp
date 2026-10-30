#include "sceneManager.h"
#include <iostream>

SceneManager::SceneManager() : currentScene(nullptr) {}


SceneManager& SceneManager::getInstance() {
		static SceneManager instance;
		return instance;
}

SceneManager::~SceneManager() {
		for (auto& pair : scenes) {
				delete pair.second;
		}
		scenes.clear();
}

void SceneManager::addScene(const std::string& title, Scene* scene) {
		if (scene && scenes.find(title) == scenes.end()) {
				scenes[title] = scene;
		}
}

void SceneManager::removeScene(const std::string& title) {
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

void SceneManager::switchTo(const std::string& title) {
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

void SceneManager::update(float dt) {
		if (currentScene) {
				currentScene->update(dt);
		}
}

void SceneManager::render() {
		if (currentScene) {
				currentScene->render();
		}
}

Scene* SceneManager::getCurrentScene() const { return currentScene; }