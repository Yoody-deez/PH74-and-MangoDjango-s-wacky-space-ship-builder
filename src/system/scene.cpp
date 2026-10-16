#include "scene.h"

Scene::Scene(const string& t) : title(t) {}

EventManager& Scene::getEventManager() { return eventManager; }
string Scene::getTitle() const { return title; }