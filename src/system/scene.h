#pragma once
#include <string>
#include "EventManager.h"

using namespace std;

class Scene {
protected:
    std::string title;
    EventManager eventManager;

public:
    Scene(const string& t);
    virtual ~Scene() = default;

    virtual void load() = 0;
    virtual void unload() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;

    EventManager& getEventManager();
    string getTitle() const;
};