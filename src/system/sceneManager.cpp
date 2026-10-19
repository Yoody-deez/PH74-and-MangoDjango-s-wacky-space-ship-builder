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

void SceneManager::addScene(const string& title, Scene* scene) {
		if (scene && scenes.find(title) == scenes.end()) {
				scenes[title] = scene;
		}
}

void SceneManager::removeScene(const string& title) {
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

void SceneManager::switchTo(const string& title) {
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