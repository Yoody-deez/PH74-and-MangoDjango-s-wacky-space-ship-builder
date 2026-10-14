#pragma once
#include <string>
#include "../system/event.h"
#include "../graphics/resourceManager.h"
#include "../core/vector2.h"

class visualControl : public EventObserver {
protected:
    Vector2 position;
    Vector2 size;

public:
    virtual ~visualControl() = default;

    virtual void render() = 0;
    virtual void setPosition(Vector2 pos) { position = pos; }
    virtual void setSize(Vector2 s) { size = s; }
    
    void onEvent(Event e) override {}
};