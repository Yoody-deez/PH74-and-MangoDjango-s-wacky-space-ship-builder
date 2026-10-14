#pragma once
#include <string>
#include "EventManager.h"

class scene {
protected:
    std::string title;
    EventManager eventManager;

public:
    scene(const std::string& t) : title(t) {}
    virtual ~scene() = default;

    virtual void load() = 0;
    virtual void unload() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;

    EventManager& getEventManager() { return eventManager; }
    std::string getTitle() const { return title; }
};