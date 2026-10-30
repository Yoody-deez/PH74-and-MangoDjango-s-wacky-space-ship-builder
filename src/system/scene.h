#pragma once
#include <string>
#include "EventManager.h"

class Scene {
protected:
    std::string title;
    EventManager eventManager;

public:
    Scene(const std::string& t);
    virtual ~Scene();

    virtual void load() = 0;
    virtual void unload() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;

    EventManager& getEventManager();
    std::string getTitle() const;
};