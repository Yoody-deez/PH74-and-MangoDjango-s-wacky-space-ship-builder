#include "scene.h"

Scene::Scene(const std::string& t) : title(t) {}

Scene::~Scene() = default;

EventManager& Scene::getEventManager() { return eventManager; }
std::string Scene::getTitle() const { return title; }